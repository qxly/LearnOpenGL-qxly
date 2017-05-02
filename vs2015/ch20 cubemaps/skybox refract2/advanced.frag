#version 330 core

out vec4 color;

uniform samplerCube texture1;
uniform vec3 u_cameraPos;

in vec3 v_normal;
in vec3 v_position;

void main()
{
	float ratio = 1.00 / 1.52;
	vec3 I = normalize(v_position - u_cameraPos);
	vec3 R = refract(I, normalize(v_normal), ratio);
	vec4 texColor = texture(texture1, R);
	color = texColor;
}
