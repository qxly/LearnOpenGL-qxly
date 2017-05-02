#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_fragPos;
out vec3 v_normal;
out vec2 v_texCoords;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	v_fragPos = vec3(model * vec4(position, 1.0));
	v_normal = mat3(transpose(inverse(model))) * normal;
	v_texCoords = texCoords;
};