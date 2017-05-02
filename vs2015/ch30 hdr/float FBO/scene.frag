#version 330 core

out vec4 fragColor;

uniform vec3 u_lightColor[4];
uniform vec3 u_lightPos[4];
uniform vec3 u_viewPos;
uniform sampler2D texObj;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_tex;

vec4 calculate(vec3 lightColor, vec3 lightPos){
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halfDir, norm), 0.0), 2);
	float specularStrength = 0.5;
	vec3 speculat = specularStrength * spec * lightColor;
	
	vec4 objectColor = texture(texObj, v_tex);
	vec3 result = (ambient + diffuse + speculat) * vec3(objectColor);
	
	return vec4(result, 1.0);
}

void main()
{
	for (int i = 0; i < 1; i++){
		fragColor += calculate(u_lightColor[i], u_lightPos[i]);
	}
}