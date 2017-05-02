#version 330 core

out vec4 o_color;

uniform vec3 u_viewPos;

struct Material
{
	sampler2D diffuse;
	sampler2D sam_specular;
	vec3 specular;	
	float shininess;
};
uniform Material u_material;

struct Light
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light u_light;

in vec3 v_normal;
in vec3 v_fragPos;
in vec2 v_texCoords;

void main()
{
	vec3 matdiffuse = vec3(texture(u_material.diffuse, v_texCoords));
	
	vec3 ambient = matdiffuse * u_light.ambient;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_light.position - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * matdiffuse * u_light.diffuse;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),u_material.shininess);
	vec3 specular = spec * vec3(texture(u_material.sam_specular, v_texCoords)) * u_light.specular;
	
	vec3 result;
	float theta = dot(lightDir, normalize(-u_light.direction));
	if (theta > u_light.cutoff) {
		float distance = length(u_light.position - v_fragPos);
		float attenuation = 1.0 / (u_light.constant + u_light.linear * distance + u_light.quadratic * distance * distance);
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		result = ambient + diffuse + specular;
	}
	else {
		result = ambient;
	}
	o_color = vec4(result, 1.0);
}