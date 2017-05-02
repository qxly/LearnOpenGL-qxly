#version 330 core

out vec4 fragColor;

uniform vec3 u_lightColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform sampler2D texture1;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_tex;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0),64.0);
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halfDir, norm), 0.0), 2);
	float specularStrength = 0.5;
	vec3 speculat = specularStrength * spec * u_lightColor;
	
	vec4 objectColor = texture(texture1, v_tex);
	
	// attenuation
	float dist = length(u_lightPos - v_fragPos);
	float attenuation = 1.0 / (dist);
	
	vec3 result = (ambient + diffuse + speculat) * vec3(objectColor) * attenuation;
	
	float gamma = 2.2;
	result = pow(result, vec3(1.0 / gamma));
	fragColor = vec4(result, 1.0);
}