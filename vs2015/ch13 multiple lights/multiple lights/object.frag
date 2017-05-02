#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// direction light
struct DirLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Point Light
struct PointLight
{
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Spot Light
struct SpotLight
{
	vec3 position;
	
	vec3 direction;	
	float cutOff;
	float outerCutOff;
	
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 o_color;

in vec3 v_normal;
in vec3 v_fragPos;
in vec2 v_texCoords;

uniform vec3 u_viewPos;
uniform Material u_material;
uniform DirLight u_dirLight;
#define NR_POINT_LIGHT 4
uniform PointLight u_pointLights[NR_POINT_LIGHT];
uniform SpotLight u_spotLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 flagPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 flagPos, vec3 viewDir);

void main()
{
	// 一些属性
	vec3 norm = normalize(v_normal);
	vec3 viewDir = normalize(u_viewPos - v_fragPos);
	
	// 计算平行光照
	vec3 result = calcDirLight(u_dirLight, norm, viewDir);
	
	// 计算顶点光照
	for (int i = 0; i < NR_POINT_LIGHT; i++)
	{
		result += calcPointLight(u_pointLights[i], norm, v_fragPos, viewDir);
	}
	
	// 计算聚光
	result += calcSpotLight(u_spotLight, norm, v_fragPos, viewDir);
	
	o_color = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	// 计算漫反射强度
	float diff = max(dot(normal, lightDir), 0.0);
	
	// 计算镜面反射强度
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	
	// 合并各个关照分量
	vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_texCoords));
	vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_texCoords));
	
	return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 flagPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - flagPos);
	
	// 计算漫反射强度
	float diff = max(dot(normal, lightDir), 0.0);
	
	// 计算镜面反射强度
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	
	// 计算衰减
	float distance = length(light.position - flagPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	
	// 合并各个关照分量
	vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_texCoords));
	vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_texCoords));		
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 flagPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - flagPos);
	
	// 计算漫反射强度
	float diff = max(dot(normal, lightDir), 0.0);
	
	// 计算镜面反射强度
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	
		// 计算衰减
	float distance = length(light.position - flagPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	// 计算聚光
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	
	// 合并各个关照分量
	vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_texCoords));
	vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_texCoords));	
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	
	return (ambient + diffuse + specular);
}