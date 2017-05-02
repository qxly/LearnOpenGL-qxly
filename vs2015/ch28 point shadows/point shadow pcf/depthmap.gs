#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 depthMatrices[6];
out vec4 v_fragPos;

void main(){
	for (int face = 0; face < 6; face++){
		gl_Layer = face;
		for (int v = 0; v < 3; v++){
			v_fragPos = gl_in[v].gl_Position;
			gl_Position = depthMatrices[face] * v_fragPos;
			EmitVertex();
		}
		EndPrimitive();
	}
}