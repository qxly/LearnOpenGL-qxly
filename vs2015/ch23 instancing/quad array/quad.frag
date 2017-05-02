#version 330 core

out vec4 color;

in VS_OUT{
	vec3 color;
}frag_in;

void main()
{
	color = vec4(frag_in.color, 1.0);
}
