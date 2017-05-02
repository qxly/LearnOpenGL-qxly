#version 330 core

out vec4 o_color;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

void main()
{
	o_color = vec4(u_lightColor * u_objectColor, 1.0);
}