#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texture;

out vec2 v_texture;

uniform mat4 u_mat;

void main()
{
	gl_Position = u_mat * vec4(a_pos, 1.0);
	v_texture = vec2(a_texture.x, 1.0 - a_texture.y);
};