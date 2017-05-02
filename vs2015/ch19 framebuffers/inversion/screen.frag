#version 330 core

out vec4 color;

uniform sampler2D texture1;

in vec2 v_textCoords;

void main()
{
	color = vec4(vec3(1.0 - texture(texture1, v_textCoords)), 1.0);
}
