#version 330 core

out vec4 o_color;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * u_lightColor;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),256);
	float specularStrength = 1.0;
	vec3 speculat = specularStrength * spec * u_lightColor;
	
	vec3 result = (ambient + diffuse + speculat) * u_objectColor;
	o_color = vec4(result, 1.0);
}