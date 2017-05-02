#version 330 core

layout (location = 0) in vec3 a_pos;

uniform mat4 u_mat;

void main()
{
	gl_Position = u_mat * vec4(a_pos, 1.0);
};