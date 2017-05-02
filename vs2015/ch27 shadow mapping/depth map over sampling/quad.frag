#version 330 core

out vec4 fragColor;

in vec2 a_tex;

uniform sampler2D texSample;

void main(){
	float depthValue = texture(texSample, a_tex).r;
	fragColor = vec4(vec3(depthValue), 1.0);
}