#pragma once

// glew
#include "GL/glew.h"

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

public:
	GLuint program;	// program ID
	void use();
};


