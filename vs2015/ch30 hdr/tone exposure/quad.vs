#version 330 core

layout (location = 0) in vec2 a_pos;

out vec2 a_tex;

void main(){
	gl_Position = vec4(a_pos, 0.0, 1.0);
	a_tex = a_pos * 0.5 + 0.5;
}