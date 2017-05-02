#version 330 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

uniform vec3 u_lightColor;

void main()
{
	fragColor = vec4(u_lightColor, 1.0);
	float brightness = dot(fragColor.rgb, vec3(1.0));
	float threshold = 1.0;
	if (brightness > threshold){
		brightColor = vec4(fragColor.rgb, 1.0);
	}
}