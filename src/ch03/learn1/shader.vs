#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

out vec3 v_color;
out vec4 v_pos;
uniform float u_offset;
void main()
{
	gl_Position = vec4(a_pos, 1.0);
	//gl_Position = vec4(u_offset + a_pos.x, -a_pos.y, a_pos.z, 1.0);
	v_pos = gl_Position;
	v_color = a_color;
};