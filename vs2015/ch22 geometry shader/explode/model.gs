#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 v_texCoords[];

out vec2 v_texCoords_frag;

uniform float u_time;

vec4 explode(vec4 pt, vec3 normal){
	return pt + vec4((sin(u_time) + 1.0) * normal, 0.0);
}

void main()
{	
	vec3 va = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
	vec3 vb = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
	vec3 normal = normalize(cross(va, vb));
	
	gl_Position = explode(gl_in[0].gl_Position, normal);
	v_texCoords_frag = v_texCoords[0];
	EmitVertex();
	
	gl_Position = explode(gl_in[1].gl_Position, normal);
	v_texCoords_frag = v_texCoords[1];
	EmitVertex();
	
	gl_Position = explode(gl_in[2].gl_Position, normal);
	v_texCoords_frag = v_texCoords[2];
	EmitVertex();
	
	EndPrimitive();
}