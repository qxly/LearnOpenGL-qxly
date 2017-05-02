#version 330 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform sampler2D texObj;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_tex;

void main()
{
	vec4 objectColor = texture(texObj, v_tex);
	//float distance = length(v_fragPos - u_lightPos);
	float ambientStrength = 0.5;
	//vec3 ambient = ambientStrength * u_lightColor;
	vec3 ambient = ambientStrength * objectColor.rgb;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor * vec3(objectColor);
	
	//vec3 viewDir = normalize(u_viewPos - v_fragPos);
	//vec3 halfDir = normalize(lightDir + viewDir);
	//float spec = pow(max(dot(halfDir, norm), 0.0), 64);
	//float specularStrength = 0.5;	
	//vec3 speculat = specularStrength * spec * u_lightColor;

	//vec3 result = (ambient + diffuse + speculat) * vec3(objectColor);
		
	vec3 result = ambient + diffuse;
	fragColor = vec4(result, 1.0);
	
	float brightness = dot(fragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	float threshold = 1.0;
	if (brightness > threshold){
		brightColor = vec4(fragColor.rgb, 1.0);
	}
}