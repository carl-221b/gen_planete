#version 330 core

out vec4 out_color;
in vec3 color_frag;

void main(void) {
    out_color = vec4(color_frag,1);
}
