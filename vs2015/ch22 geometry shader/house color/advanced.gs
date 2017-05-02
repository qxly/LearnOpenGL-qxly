#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT{
	vec3 i_color;
}gs_in[];

out vec3 v_color;

void build_house(vec4 pt){
	v_color = gs_in[0].i_color;
	gl_Position = pt + vec4(-0.1, -0.1, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pt + vec4(0.1, -0.1, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pt + vec4(-0.1, 0.1, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pt + vec4(0.1, 0.1, 0.0, 0.0);
	EmitVertex();

	v_color = vec3(1.0, 1.0, 1.0);
	gl_Position = pt + vec4(0.0, 0.2, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}

void main()
{
	build_house(gl_in[0].gl_Position);
}