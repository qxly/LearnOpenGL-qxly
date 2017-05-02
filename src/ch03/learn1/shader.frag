#version 330 core

in vec3 v_color;
out vec4 o_color;

in vec4 v_pos;

void main()
{
	//o_color = vec4(v_color, 1.0);
	o_color = v_pos;
}