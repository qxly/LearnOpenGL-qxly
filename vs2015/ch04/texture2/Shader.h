#ifndef SHADER_h
#define SHADER_h

// glew
#define GLEW_STATIC
#include "../../../dep/inc/GL/glew.h"

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

public:
	GLuint _program;	// program ID
	void use();
};

#endif

