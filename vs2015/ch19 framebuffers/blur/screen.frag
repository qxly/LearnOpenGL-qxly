#version 330 core

out vec4 color;

uniform sampler2D texture1;

in vec2 v_textCoords;

const float offset = 1.0 / 300;
void main()
{
	    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right
    );
	
	float kernel[9] = float[](
		1, 2, 1,
		2, 4, 2, 
		1, 2, 1
	);

	
	vec3 col = vec3(0.0);
	for (int i = 0; i < 9; i++)
	{
		col += vec3(texture(texture1, v_textCoords.st + offsets[i])) * kernel[i];
	}
	
	color = vec4(col / 16.0, 1.0);
}
