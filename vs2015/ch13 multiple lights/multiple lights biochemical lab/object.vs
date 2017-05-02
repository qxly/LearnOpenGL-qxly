#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoords;

uniform mat4 u_mat;
uniform mat4 u_matModel;

out vec3 v_normal;
out vec3 v_fragPos;
out vec2 v_texCoords;

void main()
{
	gl_Position = u_mat * vec4(a_pos, 1.0);
	v_fragPos = vec3(u_matModel * vec4(a_pos, 1.0));
	v_normal = mat3(transpose(inverse(u_matModel))) * a_normal;
	v_texCoords = a_texCoords;
}