#version 330 core

out vec4 fragColor;

in vec2 a_tex;

uniform sampler2D texSample;
uniform bool hdr;
uniform float exposure;

void main(){
	vec3 objColor = texture(texSample, a_tex).rgb;
	if (hdr){
		vec3 mapped = vec3(1.0) - exp(-objColor * exposure);
	
		const float gamma = 2.2;
		mapped = pow(mapped, vec3(1.0/gamma));
	
		fragColor = vec4(mapped, 1.0);
	} else{
		fragColor = vec4(objColor, 1.0);
	}
}