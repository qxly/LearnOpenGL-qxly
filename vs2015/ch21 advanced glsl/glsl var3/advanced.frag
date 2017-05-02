#version 330 core

out vec4 color;

in vec3 v_normal;
in vec3 v_position;

void main()
{
	if(gl_FrontFacing){
		color = vec4(1.0, 0.0, 0.0, 1.0);
	} else{
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}
}
