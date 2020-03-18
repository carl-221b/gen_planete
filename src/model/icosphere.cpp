#include "icosphere.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <limits>

using namespace std;
using namespace Eigen;
using namespace surface_mesh;

Icosphere::Icosphere(int nbSubdivision, bool organicLook) {
    _vertices = new Vertices;

    load(DATA_DIR"/models/icosa.obj");

    for(int i = 1; i < nbSubdivision; i++){
        this->subdivide();
    }

    if(organicLook){
        this->organicTriangulation();
    }
}

Icosphere::~Icosphere()
{

    delete _vertices;
}

void Icosphere::computeNormals()
{
    // pass 1: set the normal tangent and bitangent to 0

    for(unsigned int i = 0; i <  _vertices->_normals.size(); i++){
        _vertices->_normals[i]=Vector3f(0,0,0);
    }

    // pass 2: compute face normals and accumulate

    for(unsigned int i = 0; i <  _faces.size(); i++)
    {
         Vector3i& face = _faces[i];

         Vector3f& p0 =  _vertices->_positions[face.x()];
         Vector3f& p1 =  _vertices->_positions[face.y()];
         Vector3f& p2 =  _vertices->_positions[face.z()];


         Vector3f q1 = p1-p0;
         Vector3f q2 = p2-p0;

         _vertices->_normals[face.x()] += q1.cross(q2);
         _vertices->_normals[face.y()] += q1.cross(q2);
         _vertices->_normals[face.z()] += q1.cross(q2);

    }
    // pass 3: normalize

    for(unsigned int i = 0; i <  _vertices->_normals.size(); i++){
        _vertices->_normals[i]=_vertices->_normals[i].normalized();
    }

}


void Icosphere::load(const string& filename)
{
    //cerr << "Loading: " << filename << endl;

    _halfEdge.read(filename);
    updateMeshFromSurfaceMesh();
}

void Icosphere::updateMeshFromSurfaceMesh()
{
    if(!_halfEdge.is_triangle_mesh())
        _halfEdge.triangulate();

    _halfEdge.update_face_normals();
    _halfEdge.update_vertex_normals();

    _vertices->_positions.resize(0);
    _vertices->_normals.resize(0);
    _vertices->_colors.resize(0);

    _vertices->_positions.reserve(_halfEdge.vertices_size());
    _vertices->_normals.reserve(_halfEdge.vertices_size());
    //_vertices->_colors.reserve(_halfEdge.vertices_size()*3);

    // vertex properties
    Surface_mesh::Vertex_property<Point> vertices = _halfEdge.get_vertex_property<Point>("v:point");
    Surface_mesh::Vertex_property<Point> vnormals = _halfEdge.get_vertex_property<Point>("v:normal");

    // vertex iterator
    Surface_mesh::Vertex_iterator vit;

    for(vit = _halfEdge.vertices_begin(); vit != _halfEdge.vertices_end(); ++vit)
    {
        _vertices->_positions.push_back(vertices[*vit]);
        _vertices->_normals.push_back(vnormals[*vit]);
        //Push R, then G, then B
        Eigen::Vector3f vect = {0.0f,1.0f,1.0f};
        _vertices->_colors.push_back(vect);

        _bbox.extend(vertices[*vit]);
    }

    _faces.resize(0);

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
            _faces.push_back(Vector3i(v0.idx(), v1.idx(), v2.idx()));
        } while (++fvit != fvend);
    }
    //saveOBJ();
    //saveOFF();
}

void Icosphere::subdivide()
{
    Surface_mesh _nextHalfEdge;

    Surface_mesh::Vertex_property<Point> vertices = _halfEdge.get_vertex_property<Point>("v:point");
    Surface_mesh::Vertex_property<Surface_mesh::Vertex> vertex_mapping = _halfEdge.add_vertex_property<Surface_mesh::Vertex>("v:mapping");
    Surface_mesh::Edge_property<Surface_mesh::Vertex> edge_mapping = _halfEdge.add_edge_property<Surface_mesh::Vertex>("e:mapping");

    Surface_mesh::Vertex_iterator vit;
    Surface_mesh::Edge_iterator eit;
    Surface_mesh::Face_iterator fit;

    //Step 1
    for(vit = _halfEdge.vertices_begin(); vit != _halfEdge.vertices_end(); ++vit)
    {
        Point vi = vertices[*vit];
        vertex_mapping[*vit] = _nextHalfEdge.add_vertex(vi);
    }

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

    //Step 2
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

    //Step 3
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
        nextVertices[vertex_mapping[*vit]] = vi_prime;
    }

    //Step 4
    _halfEdge = _nextHalfEdge;
    updateMeshFromSurfaceMesh();
}


Icosphere::Vertices* Icosphere::getVertices(){
    return _vertices;
}


void Icosphere::organicTriangulation(){
    Vertices* vertices = this->getVertices();

    float dist_min =  MAXFLOAT;
    // Iterate vertices
    for( Surface_mesh::Vertex v: _halfEdge.vertices())
    {
        Vector3f origin = vertices->_positions[v.idx()];

        // Iterate neighbours
        Surface_mesh::Vertex_around_vertex_circulator circ(&_halfEdge, v);
        for(Surface_mesh::Vertex vd : circ)
        {
            Vector3f dest = vertices->_positions[vd.idx()];
            Vector3f vect = dest - origin;

            //Find radius sphere minimal.
            if(vect.norm() < dist_min)
            {
                dist_min = vect.norm();
                //std::cout<< dist_min <<std::endl;
            }
        }
        // Random displacement in a sphere of radius dist_min
        origin.x() += rand() % 2*dist_min -dist_min;
        origin.y() += rand() % 2*dist_min -dist_min;
        origin.z() += rand() % 2*dist_min -dist_min;
        vertices->_positions[v.idx()]= origin;
    }

    /*
    for(int i = 0; i < vertices->_positions.size(); i++){
        float factor = (980.0+ std::rand()%50) / 1000.0;
        vertices->_positions[i] += vertices->_normals[i] * factor; //faire perpendiculaire à _normals
        //ou solution Marc (discord)
        //ou : https://experilous.com/1/blog/post/procedural-planet-generation
    }
    */

    //updateMeshFromSurfaceMesh();
}
