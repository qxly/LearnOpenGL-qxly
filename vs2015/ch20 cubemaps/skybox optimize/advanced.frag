#version 330 core

out vec4 color;

uniform sampler2D texture1;

in vec2 v_textCoords;

void main()
{
	vec4 texColor = texture(texture1, v_textCoords);
	color = texColor;
}
