#version 330 core

uniform mat4 projection_matrix;
uniform mat4 model_view_matrix;

in vec3 vtx_position;

in vec3 color_f;
out vec3 color_frag;

void main()
{
    gl_Position = projection_matrix * model_view_matrix * vec4(vtx_position, 1.);
    color_frag = vec3(255,255,255);
}
