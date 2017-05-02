#version 330 core

out vec4 color;

uniform sampler2D texture1;

in vec2 v_textCoords;

float linearizeDepth(float depth)
{
	float near = 0.1;
	float far  = 100.0;
	float z = depth * 2.0 - 1.0;
	return (2.0 * near) / (far + near - z * (far - near));
}

void main()
{
	color = texture(texture1, v_textCoords);
	color = vec4(vec3(gl_FragCoord.z), 1.0);
	//float depth = linearizeDepth(gl_FragCoord.z);
	//color = vec4(vec3(depth), 1.0);
}
