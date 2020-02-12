#version 330 core

uniform mat4 obj_mat;
uniform mat4 view_mat;
uniform mat4 proj_mat;

in vec3 vtx_position;
in vec4 vtx_color;

out vec4 var_color;

void main()
{
  vec4 new_pos =  proj_mat * view_mat * obj_mat * vec4(vtx_position, 1.);
  gl_Position = new_pos;
  var_color = vec4(vtx_color.rgb, 1.);
}
