#version 330 core

uniform mat4 projection_matrix;
uniform mat4 model_view_matrix;

in vec3 vtx_position;

void main()
{
    gl_Position = projection_matrix * model_view_matrix * vec4(vtx_position, 1.);
}
