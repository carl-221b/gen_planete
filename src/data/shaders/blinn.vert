#version 330 core

uniform mat4 projection_matrix;
uniform mat4 model_view_matrix;
uniform mat3 normal_matrix;
uniform mat4 model_matrix;

in vec3 vtx_position;
in vec3 vtx_color;
in vec3 vtx_normal;

out vec4 vert_pos_view;
out vec3 vert_normal_view;
flat out vec3 v_color;

void main()
{
    gl_Position = projection_matrix * model_view_matrix * vec4(vtx_position,1.0);

    vert_pos_view  = normalize(model_view_matrix * vec4(vtx_position,1.0));
    vert_normal_view = normalize(normal_matrix * vtx_normal);
    v_color=vtx_color;
}
