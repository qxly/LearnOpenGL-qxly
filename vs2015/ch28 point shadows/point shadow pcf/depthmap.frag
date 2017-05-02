#version 330 core

uniform vec3 u_lightPos;
uniform float far_plane;

in vec4 v_fragPos;

void main(){
	float lightDistance = length(u_lightPos - v_fragPos.xyz);
	gl_FragDepth = lightDistance / far_plane;
}