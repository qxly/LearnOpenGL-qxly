#version 330 core

out vec4 color;

uniform sampler2D texture1;

in vec2 v_textCoords;

void main()
{
	color = texture(texture1, v_textCoords);
	//float average = (color.r + color.g + color.b) / 3.0;
	float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	color = vec4(average, average, average, 1.0);
}
