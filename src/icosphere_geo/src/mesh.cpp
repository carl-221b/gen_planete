#include "mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <math.h>

#define NB_SUBDIVISE 5

using namespace std;
using namespace Eigen;
using namespace surface_mesh;

Mesh::~Mesh()
{
    if(_ready){
        glDeleteBuffers(1, &_indicesBuffer);
        glDeleteBuffers(2, _vbo);
        glDeleteVertexArrays(1,&_vao);
    }
}

void Mesh::load(const string& filename)
{
    cerr << "Loading: " << filename << endl;

    _halfEdge.read(filename);
    load();
}

void Mesh::load()
{
    if(!_halfEdge.is_triangle_mesh())
        _halfEdge.triangulate();

    _halfEdge.update_face_normals();
    _halfEdge.update_vertex_normals();

    _positions.resize(0);
    _normals.resize(0);
    _positions.reserve(_halfEdge.vertices_size());
    _normals.reserve(_halfEdge.vertices_size());

    // vertex properties
    Surface_mesh::Vertex_property<Point> vertices = _halfEdge.get_vertex_property<Point>("v:point");
    Surface_mesh::Vertex_property<Point> vnormals = _halfEdge.get_vertex_property<Point>("v:normal");

    // vertex iterator
    Surface_mesh::Vertex_iterator vit;

    for(vit = _halfEdge.vertices_begin(); vit != _halfEdge.vertices_end(); ++vit)
    {
        _positions.push_back(vertices[*vit]);
        _normals.push_back(vnormals[*vit]);
        _bbox.extend(vertices[*vit]);
    }

    _indices.resize(0);

    // face iterator
    Surface_mesh::Face_iterator fit, fend = _halfEdge.faces_end();
    // vertex circulator
    Surface_mesh::Vertex_around_face_circulator fvit, fvend;
    Surface_mesh::Vertex v0, v1, v2;
    for (fit = _halfEdge.faces_begin(); fit != fend; ++fit)
    {
        fvit = fvend = _halfEdge.vertices(*fit);
        v0 = *fvit;
        ++fvit;
        v2 = *fvit;

        do{
            v1 = v2;
            ++fvit;
            v2 = *fvit;
            _indices.push_back(Vector3i(v0.idx(), v1.idx(), v2.idx()));
        } while (++fvit != fvend);
    }
    saveOBJ();
    saveOFF();
}

void Mesh::saveOBJ()
{
    std::ofstream myfile;
    myfile.open ("suzanne.obj");
    myfile << "o suzanne\n";

    for(unsigned int i=0; i<_positions.size(); i++){
        Eigen::Vector3f p = _positions.at(i);
        myfile << "v " << p.x() << " " << p.y() << " " << p.z() << "\n";
        Eigen::Vector3f n = _normals.at(i);
        myfile << "vn " << n.x() << " " << n.y() << " " << n.z() << "\n";

    }

    for(unsigned int i=0; i<_indices.size(); i++){
        Eigen::Vector3i f = _indices.at(i);
        myfile << "f " << ( std::to_string(f.x()+1)+"//"+std::to_string(f.x()+1) ) << " " << ( std::to_string(f.y()+1)+"//"+std::to_string(f.y()+1) ) << " " << ( std::to_string(f.z()+1)+ "//" +std::to_string(f.z()+1) ) << "\n";
    }


    myfile.close();
}

void Mesh::saveOFF(){
    std::ofstream myfile;
    myfile.open ("suzanne.off");
    myfile << "OFF\n";
    myfile << _positions.size() << " " << numFaces() << " 0\n"; // 0 is the (ignored) number of edges

    for(unsigned int i=0; i<_positions.size(); i++){
        Eigen::Vector3f p = _positions.at(i);
        myfile << p.x() << " " << p.y() << " " << p.z() << "\n";
    }

    for(unsigned int i=0; i<_indices.size(); i++){
        Eigen::Vector3i f = _indices.at(i);
        myfile << "3 " << f.x() << " " << f.y() << " " << f.z() << "\n";
    }
}

void Mesh::init()
{
    for(int i = 0; i < NB_SUBDIVISE; i++){
        subdivide();
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(2, _vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*_positions.size(), _positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*_normals.size(), _normals.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &_indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3i)*_indices.size(), _indices.data(),  GL_STATIC_DRAW);

    glBindVertexArray(0);

    _ready = true;
}

void Mesh::specifyVertexData(Shader *shader)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    int pos_loc = shader->getAttribLocation("vtx_position");
    glEnableVertexAttribArray(pos_loc);
    glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    int normal_loc = shader->getAttribLocation("vtx_normal");
    if(normal_loc>=0){
        glEnableVertexAttribArray(normal_loc);
        glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);
    }
}

void Mesh::display(Shader *shader)
{
    if (!_ready)
        init();

    glBindVertexArray(_vao);

    specifyVertexData(shader);

    glDrawElements(GL_TRIANGLES, _indices.size()*3,  GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::subdivide()
{
    Surface_mesh _nextHalfEdge;

    Surface_mesh::Vertex_property<Point> vertices = _halfEdge.get_vertex_property<Point>("v:point");
    Surface_mesh::Vertex_property<Surface_mesh::Vertex> vertex_mapping = _halfEdge.add_vertex_property<Surface_mesh::Vertex>("v:mapping");
    Surface_mesh::Edge_property<Surface_mesh::Vertex> edge_mapping = _halfEdge.add_edge_property<Surface_mesh::Vertex>("e:mapping");

    Surface_mesh::Vertex_iterator vit;
    Surface_mesh::Edge_iterator eit;
    Surface_mesh::Face_iterator fit;

    //Etape 1
    //copie des points de _halfEdge dans _nextHalfEdge
    for(vit = _halfEdge.vertices_begin(); vit != _halfEdge.vertices_end(); ++vit)
    {
        Point vi = vertices[*vit];
        vertex_mapping[*vit] = _nextHalfEdge.add_vertex(vi);
    }

    //ajout point intermédiaire
    for(eit = _halfEdge.edges_begin(); eit != _halfEdge.edges_end(); ++eit)
    {
        Surface_mesh::Vertex v0, v1, v2, v3;
        Surface_mesh::Halfedge he;

        he = _halfEdge.halfedge(*eit, 0);
        v0 = _halfEdge.from_vertex(he);

        if(!_halfEdge.is_boundary(*eit)) {
            he = _halfEdge.next_halfedge(he);
            v1 = _halfEdge.to_vertex(he);
        }

        he = _halfEdge.halfedge(*eit, 1);
        v2 = _halfEdge.from_vertex(he);

        if(!_halfEdge.is_boundary(*eit)) {
            he = _halfEdge.next_halfedge(he);
            v3 = _halfEdge.to_vertex(he);
        }

        double coefEdge = 3.0/8.0, coefFace = 1.0/8.0;

        if(!_halfEdge.is_boundary(*eit)) {
            edge_mapping[*eit] = _nextHalfEdge.add_vertex(coefEdge*vertices[v0] + coefFace*vertices[v1] + coefEdge*vertices[v2] + coefFace*vertices[v3]);
        } else {
            edge_mapping[*eit] = _nextHalfEdge.add_vertex(0.5*vertices[v0] + 0.5*vertices[v2]);
        }
    }

    //Etape 2
    for(fit = _halfEdge.faces_begin(); fit != _halfEdge.faces_end(); ++fit){
        Surface_mesh::Halfedge h;
        Surface_mesh::Vertex v0, v1, v2;
        Surface_mesh::Edge e01, e12, e20;

        h = _halfEdge.halfedge(*fit);
        v0 = _halfEdge.from_vertex(h);
        e01 = _halfEdge.edge(h);

        h = _halfEdge.next_halfedge(h);
        v1 = _halfEdge.from_vertex(h);
        e12 = _halfEdge.edge(h);

        h = _halfEdge.next_halfedge(h);
        v2 = _halfEdge.from_vertex(h);
        e20 = _halfEdge.edge(h);

        std::vector<Surface_mesh::Vertex> middleFace;
        middleFace.push_back(edge_mapping[e01]);
        middleFace.push_back(edge_mapping[e12]);
        middleFace.push_back(edge_mapping[e20]);

        std::vector<Surface_mesh::Vertex> v0Face;
        v0Face.push_back(vertex_mapping[v0]);
        v0Face.push_back(edge_mapping[e01]);
        v0Face.push_back(edge_mapping[e20]);

        std::vector<Surface_mesh::Vertex> v1Face;
        v1Face.push_back(vertex_mapping[v1]);
        v1Face.push_back(edge_mapping[e12]);
        v1Face.push_back(edge_mapping[e01]);

        std::vector<Surface_mesh::Vertex> v2Face;
        v2Face.push_back(vertex_mapping[v2]);
        v2Face.push_back(edge_mapping[e20]);
        v2Face.push_back(edge_mapping[e12]);

        _nextHalfEdge.add_face(middleFace);
        _nextHalfEdge.add_face(v0Face);
        _nextHalfEdge.add_face(v1Face);
        _nextHalfEdge.add_face(v2Face);
    }

    //Etape 3
    Surface_mesh::Vertex_property<Point> nextVertices = _nextHalfEdge.get_vertex_property<Point>("v:point");
    for(vit = _halfEdge.vertices_begin(); vit != _halfEdge.vertices_end(); ++vit)
    {
        Point vi = vertices[*vit];
        unsigned int di = _halfEdge.valence(*vit);
        double B = 0.0;
        if(di > 3){
            double DI = (double) di;
            B = (1.0/DI)*(5.0/8.0 - ( pow((3.0/8.0) + (1.0/4.0)*cos(2.0*M_PI/DI), 2.0)) );
        }else{
            B = 3.0/16.0;
        }

        Point sum_neighbour = vertices[*vit] - vertices[*vit];
        Surface_mesh::Vertex_around_vertex_circulator vvit;
        vvit = _halfEdge.vertices(*vit);
        unsigned int cpt = 1;
        do{
            sum_neighbour = sum_neighbour + _halfEdge.position(*vvit);
            ++vvit;
            ++cpt;
        } while (cpt <= di);

        Point vi_prime = (1.0-B*di)*vi + B*sum_neighbour;

        //cas paticulier (bords ouverts) non implémenté car inutile pour icosphere

        nextVertices[vertex_mapping[*vit]] = vi_prime;
    }

    //Etape 4
    _halfEdge = _nextHalfEdge;
    load();
    //init();

    /*
    printf("NB VERTICES : %u \n", _halfEdge.vertices_size());
    printf("NB FACES : %u \n", _halfEdge.faces_size());
    printf("--------------------\n");
    fflush(stdout);
    */
}

/* TODO */
void Mesh::edit(Editor *edit){
    _halfEdge = edit->modifyShape(_halfEdge);
    load();
}

