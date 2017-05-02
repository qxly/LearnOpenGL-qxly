#version 330 core

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_reflection1;
uniform samplerCube skybox;
uniform vec3 u_cameraPos;

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texCoords;

void main()
{
	// diffuse
	vec4 diffuse_color = texture(texture_diffuse1, v_texCoords);
	
	// reflection
	vec3 I = normalize(v_position - u_cameraPos);
	vec3 R = reflect(I, normalize(v_normal));
	float reflect_intensity = texture(texture_reflection1, v_texCoords).a;
	vec4 reflect_color;
	if (reflect_intensity > 0.1){
		reflect_color = texture(skybox, R) * 0.3;
	}
	
	color = diffuse_color + reflect_color;
}
