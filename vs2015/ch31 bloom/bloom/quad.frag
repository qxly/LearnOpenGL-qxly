#version 330 core

out vec4 fragColor;

in vec2 a_tex;

uniform sampler2D texScene;
uniform sampler2D texBlur;

void main(){
	vec3 hdrColor = texture(texScene, a_tex).rgb;
	vec3 blurColor = texture(texBlur, a_tex).rgb;
	hdrColor += blurColor;
	float exposure = 1.0;
	vec3 result = vec3(1.0) - exp(-hdrColor * 2.5);
	//vec3 result = hdrColor / (hdrColor + vec3(1.0));
	result = pow(result, vec3(1.0 / 2.2));
	
	fragColor = vec4(result, 1.0);
}