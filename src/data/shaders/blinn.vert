#version 330 core

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
out vec3 vert_normal_view;
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
    }
    else
    {   
        v_color = vec4(0.0,0.4,0.6,0.7);
        gl_Position = projection_matrix * model_view_matrix * vec4(0.708*vtx_position/length(vtx_position),1.0);
        v_shininess= 40.0;
        v_diffuse = 1.0;
        v_spec = 10.0;
    }
    

    vert_pos_view  = normalize(model_view_matrix * vec4(vtx_position,1.0));
    vert_normal_view = normalize(normal_matrix * vtx_normal);
    
}
