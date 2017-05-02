#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex;
layout (location = 3) in vec3 a_tangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

out vec3 v_fragPos;
out vec2 v_tex;

out vec3 v_lightPos;
out vec3 v_viewPos;

void main()
{
    gl_Position = projection * view * model * vec4(a_pos, 1.0f);
	v_fragPos = vec3(model * vec4(a_pos, 1.0));
	v_tex = a_tex;
	
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * a_tangent);
	vec3 N = normalize(normalMatrix * a_normal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N,T);
	
	mat3 TBN = transpose(mat3(T, B, N));
	v_lightPos = TBN * u_lightPos;
	v_viewPos = TBN * u_viewPos;
	v_fragPos = TBN * v_fragPos;
}