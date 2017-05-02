#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT{
	vec3 normal;
}gs_in[];

void generateNormal(int index){
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	
	gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal * 0.01, 0.0);
	EmitVertex();
	
	EndPrimitive();
}

void main()
{
	generateNormal(0);
	generateNormal(1);
	generateNormal(2);
}