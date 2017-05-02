#version 330 core

out vec4 o_color;

uniform vec3 u_viewPos;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material u_material;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light u_light;

in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
	vec3 ambient = u_material.ambient * u_light.ambient;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_light.position - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_material.diffuse * u_light.diffuse;
	
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),u_material.shininess);
	//float specularStrength = 0.5;
	vec3 specular = spec * u_material.specular * u_light.specular;
	
	vec3 result = ambient + diffuse + specular;
	o_color = vec4(result, 1.0);
}