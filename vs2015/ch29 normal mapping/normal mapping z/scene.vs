#version 330 core

layout (location = 0) in vec2 a_pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 v_fragPos;
out vec2 v_tex;

void main()
{
	gl_Position = projection * view * model * vec4(a_pos, 0.0, 1.0);
	v_fragPos = vec3(model * vec4(a_pos, 0.0, 1.0));
	v_tex = a_pos * 0.5 + 0.5;
};