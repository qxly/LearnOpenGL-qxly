#version 330 core

in vec2 v_texture;

out vec4 o_color;

uniform sampler2D u_image;
uniform sampler2D u_image2;

void main()
{
	o_color = mix(texture(u_image, v_texture), texture(u_image2, v_texture), 0.2);
}