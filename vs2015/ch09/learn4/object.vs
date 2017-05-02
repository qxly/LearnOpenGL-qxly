#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_mat;
uniform mat4 u_matModel;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

out vec3 v_normal;
out vec3 v_fragPos;
out vec3 v_resultColor;

void main()
{
	gl_Position = u_mat * vec4(a_pos, 1.0);
	v_fragPos = vec3(u_matModel * vec4(a_pos, 1.0));
	v_normal = mat3(transpose(inverse(u_matModel))) * a_normal;
	
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),256);
	float specularStrength = 0.5;
	vec3 speculat = specularStrength * spec * u_lightColor;
	
	v_resultColor = (ambient + diffuse + speculat) * u_objectColor;
};