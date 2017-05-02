#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 v_normal;
out vec3 v_position;
out vec2 v_texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	v_normal = mat3(transpose(inverse(model))) * normal;
	v_position = vec3(model * vec4(position, 1.0));
	v_texCoords = texCoords;
}