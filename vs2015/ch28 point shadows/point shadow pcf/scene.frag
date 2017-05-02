#version 330 core

out vec4 color;

uniform vec3 u_lightColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform sampler2D texObj;
uniform samplerCube texDepth;
uniform float far_plane;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_tex;

float shadowCalculate(vec3 lightDir){
	vec3 fragTolight = v_fragPos - u_lightPos;
	float currenDepth = length(fragTolight);
	float bias = max(0.05 * (1.0 - dot(lightDir, v_normal)), 0.005);
/*	
	float shadow = 0.0;
	float samples = 4.0;
	float offset = 0.1;
	float offsetper = offset * 2.0 / samples;
	for (float x = -offset; x < offset; x += offsetper){
		for (float y = -offset; y < offset; y += offsetper){
			for (float z = -offset; z < offset; z += offsetper){
				float closestDepth = texture(texDepth, fragTolight + vec3(x, y, z)).r;
				closestDepth *= far_plane;	
				shadow += (currenDepth - bias) < closestDepth ? 0.0 : 1.0;	
			}
		}
	}
	
	return shadow /= (samples * samples * samples);
*/
	float shadow = 0.0;
	int samples = 20;
	float viewDistance = length(u_viewPos - v_fragPos);
	//float distRadius = 0.05;
	float distRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
	vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);
	for (int i = 0; i < samples; i++){
		float closestDepth = texture(texDepth, fragTolight + sampleOffsetDirections[i] * distRadius).r;
		closestDepth *= far_plane;	
		shadow += (currenDepth - bias) < closestDepth ? 0.0 : 1.0;
	}
	return shadow / float(samples);
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