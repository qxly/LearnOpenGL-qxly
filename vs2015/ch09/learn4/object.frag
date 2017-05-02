#version 330 core

out vec4 o_color;

in vec3 v_resultColor;

void main()
{

	o_color = vec4(v_resultColor, 1.0);
}