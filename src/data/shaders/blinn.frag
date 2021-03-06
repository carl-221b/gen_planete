#version 330 core

uniform vec3 light_dir_world;
//uniform vec3 colorV = vec3(1,1,1);

in float v_diffuse;
in float v_spec;
in float v_shininess;
in vec4 vert_pos_view;
flat in vec3 vert_normal_view;
flat in vec4 v_color;

out vec4 out_color;

vec3 shade(vec3 N, vec3 L, vec3 V, 
           vec3 color, float Ka, float Kd, float Ks,
           vec3 lightCol, float shininess){

    vec3 final_color = color*Ka*lightCol;	//ambient

    float lambertTerm = dot(N,L);		//lambert

    if(lambertTerm > 0.0) {
        final_color += color*Kd*lambertTerm*lightCol; 	//diffuse

        vec3 R = reflect(L,N);
        float specular = pow(max(dot(R,V), 0.0), shininess);
        final_color += color*Ks*lightCol*(specular);	//specular
    }

    return final_color;
}

void main(void)
{
    vec3 light_color = vec3(1.0,1.0,1.0);
    out_color.rgb = shade(normalize(vert_normal_view), normalize(light_dir_world),normalize(vert_pos_view).xyz,v_color.xyz,0.4,v_diffuse,v_spec,light_color,v_shininess);
    out_color.a = v_color.a;
}
