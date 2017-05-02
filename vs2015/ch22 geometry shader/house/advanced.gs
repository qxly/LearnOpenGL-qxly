#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;


void build_house(vec4 pt){
	gl_Position = pt + vec4(-0.1, -0.1, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pt + vec4(0.1, -0.1, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pt + vec4(-0.1, 0.1, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pt + vec4(0.1, 0.1, 0.0, 0.0);
	EmitVertex();

	gl_Position = pt + vec4(0.0, 0.2, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}

void main()
{
	build_house(gl_in[0].gl_Position);
}