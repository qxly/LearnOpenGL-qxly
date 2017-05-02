#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VS_OUT{
	vec3 normal;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
	vs_out.normal = vec3(projection * vec4(normalMatrix * normal, 1.0));
}