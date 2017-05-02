#version 330 core

in vec3 v_color;
in vec2 v_texture;

out vec4 o_color;

uniform sampler2D u_image;
uniform sampler2D u_image2;

void main()
{
	//o_color = vec4(v_color, 1.0);
	//o_color = texture(u_image2, v_texture);
	//o_color = texture(u_image, v_texture) * vec4(v_color, 1.0);
	o_color = mix(texture(u_image, v_texture), texture(u_image2, vec2(1.0 - v_texture.x, v_texture.y)), 0.2);
}