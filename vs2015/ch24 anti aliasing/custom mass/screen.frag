#version 330 core

out vec4 color;

uniform sampler2DMS texture1;

in vec2 v_textCoords;

void main()
{
    vec2 tcoord = vec2(v_textCoords.x * 800.0 * 4, v_textCoords.y * 600.0 *4);
    ivec2 tst = ivec2(tcoord.x, tcoord.y);
	color = texelFetch(texture1, tst, 3);
}
