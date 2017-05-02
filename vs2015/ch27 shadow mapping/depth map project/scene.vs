#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

out vec3 v_fragPos;
out vec3 v_normal;
out vec2 v_tex;
out vec4 v_fragPosLightSpace;

void main()
{
	gl_Position = projection * view * model * vec4(a_pos, 1.0);
	v_fragPos = vec3(model * vec4(a_pos, 1.0));
	v_normal = mat3(transpose(inverse(model))) * a_normal;
	v_tex = a_tex;
	
	v_fragPosLightSpace = lightSpaceMatrix * vec4(v_fragPos, 1.0);
};