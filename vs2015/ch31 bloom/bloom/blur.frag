#version 330 core

out vec4 fragColor;

in vec2 a_tex;

uniform sampler2D image;
uniform bool horizontal;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main(){
	vec2 texSize = 1.0 / textureSize(image, 0);
	vec2 offset;	
	vec3 result;
	result = texture(image, a_tex).rgb * weight[0];
	for (int i = 1; i < 5; i++){
		if (horizontal){
		offset = vec2(texSize.x, 0.0);
	}else{
		offset = vec2(0.0, texSize.y);
	}
		offset *= i;
		result += texture(image, a_tex + offset).rgb * weight[i];
		result += texture(image, a_tex - offset).rgb * weight[i];		
	}
	
	fragColor = vec4(result, 1.0);
}