#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_mat;
uniform mat4 u_matModel;
uniform mat4 u_matView;
uniform vec3 u_lightPos;

out vec3 v_normal;
out vec3 v_fragPos;
out vec3 v_lightPos;

void main()
{
	gl_Position = u_mat * vec4(a_pos, 1.0);
	v_fragPos = vec3(u_matView * u_matModel * vec4(a_pos, 1.0));
	v_normal = mat3(transpose(inverse(u_matView * u_matModel))) * a_normal;
	v_lightPos = vec3(u_matView * vec4(u_lightPos, 1.0));
};