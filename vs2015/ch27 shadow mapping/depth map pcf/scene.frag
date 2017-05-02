#version 330 core

out vec4 color;

uniform vec3 u_lightColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform sampler2D texObj;
uniform sampler2D texDepth;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_tex;
in vec4 v_fragPosLightSpace;

float shadowCalculate(vec3 lightDir){
	vec3 projCoords = v_fragPosLightSpace.xyz / v_fragPosLightSpace.w;
	if (projCoords.z > 1.0){
		return 0.0;
	}
	projCoords = projCoords * 0.5 + 0.5;
	float bias = max(0.05 * (1.0 - dot(lightDir, v_normal)), 0.005);
	float shadow = 0.0;
	vec2 texSize = 1.0 / textureSize(texDepth, 0);
	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			float closestDepth = texture(texDepth, projCoords.xy + vec2(i,j) * texSize).r;
			float pcfShadow = (projCoords.z - bias) < closestDepth ? 0.0 : 1.0;
			shadow += pcfShadow;
		}
	}
	
	return shadow / 9.0;
}

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
	
	vec4 objectColor = texture(texObj, v_tex);
	float shadow = shadowCalculate(lightDir);
	vec3 result = (ambient + (diffuse + speculat) * (1.0 - shadow)) * vec3(objectColor);
	
	color = vec4(result, 1.0);
}