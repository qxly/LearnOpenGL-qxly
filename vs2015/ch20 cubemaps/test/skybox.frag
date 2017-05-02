#version 330 core

out vec4 color;

uniform samplerCube texture1;

in vec3 v_textCoords;

void main()
{
	vec4 texColor = texture(texture1, v_textCoords);
	color = texColor;
}
