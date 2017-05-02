#version 330 core

out vec4 fragColor;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform sampler2D texDiffuse;
uniform sampler2D texNormal;

in vec3 v_fragPos;
in vec2 v_tex;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;
	
	vec3 norm = texture(texNormal, v_tex).rgb;
	norm = normalize(norm * 2.0 - 1.0);
	//vec3 norm = vec3(0.0, 0.0, 1.0);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halfDir, norm), 0.0), 64.0);
	float specularStrength = 0.5;
	vec3 speculat = specularStrength * spec * u_lightColor;
	
	vec4 objectColor = texture(texDiffuse, v_tex);
	vec3 result = (ambient + diffuse + speculat) * vec3(objectColor);
	
	fragColor = vec4(result, 1.0);
}