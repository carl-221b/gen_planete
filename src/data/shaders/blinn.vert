#version 330 core

//uniform vec4 color_ocean = vec4(0.0,0.4,0.6,0.6); // blue
uniform vec4 color_ocean = vec4(0.4,0.2,0.3, 0.6); // Red

uniform mat4 projection_matrix;
uniform mat4 model_view_matrix;
uniform mat3 normal_matrix;
uniform mat4 model_matrix;

in vec3 vtx_position;
in vec3 vtx_color;
in vec3 vtx_normal;

out float v_diffuse;
out float v_spec;
out float v_shininess;
out vec4 vert_pos_view;
flat out vec3 vert_normal_view;
flat out vec4 v_color;

uniform int sea_mode;

void main()
{
    if(sea_mode==0)
    {
        v_color=vec4(vtx_color,1.0);
        gl_Position = projection_matrix * model_view_matrix * vec4(vtx_position,1.0);
        v_shininess=100.0;
        v_diffuse=0.9;
        v_spec = 2.0;
        vert_normal_view = normalize(normal_matrix * vtx_normal);
    }
    else
    {   

        v_color = color_ocean;
        gl_Position = projection_matrix * model_view_matrix * vec4(0.705*normalize(vtx_position),1.0);
        v_shininess= 4.0;
        v_diffuse = 1.0;
        v_spec = .9;
        vert_normal_view = normalize(normal_matrix * vtx_position);
    }
    
    vert_pos_view  = normalize(model_view_matrix * vec4(vtx_position,1.0));
}
