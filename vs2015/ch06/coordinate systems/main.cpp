#define GLEW_STATIC
// glew
#include "../../../dep/inc/GL/glew.h"
// glfw
#include "../../../dep/inc/GLFW/glfw3.h"
// SOIL
#include "../../../dep/inc/SOIL/SOIL.h"

//GLM
#include "../../../dep/inc/glm/glm.hpp"
#include "../../../dep/inc/glm/gtc/matrix_transform.hpp"
#include "../../../dep/inc/glm/gtc/type_ptr.hpp"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "../../../dep/lib_x86/debug_static/glew32sd.lib")
#pragma comment(lib, "../../../dep/lib_x86/debug_static/glfw3.lib")
#pragma comment(lib, "../../../dep/lib_x86/debug_static/SOIL.lib")

#include "Shader.h"

#include <iostream>

// key callback function
void key_callback(GLFWwindow* window, int	key, int scancode, int acion, int mode)
{
	if (key == GLFW_KEY_ESCAPE && acion == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
{
	// init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// create windows
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << "fail to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// set context
	glfwMakeContextCurrent(window);

	// init glew
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "fail to init glew" << std::endl;
		return -1;
	}

	// set viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// set keycallback
	glfwSetKeyCallback(window, key_callback);


	 //vertex data
	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	//};
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5, -0.5, 0.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5, -0.5, 0.0, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5, 0.5, 0.0, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// gen VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// gen VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// link vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// gen EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// gen texture
	GLuint texture[2];
	glGenTextures(2, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int image_w, image_h;
	unsigned char* image = SOIL_load_image("../container.jpg", &image_w, &image_h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	// gen texture2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image("../awesomeface.png", &image_w, &image_h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	// mat
	//glm::mat4 mat;
	//mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//mat = glm::scale(mat, glm::vec3(0.5, 0.5, 0.5));
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//view = glm::translate(view, glm::vec3(-0.3f, 0.2f, -3.0f));
	glm::mat4 proj;
	proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	glm::mat4 mat = proj * view * model;

	// game loop
	Shader program("../shader.vs", "../shader.frag");
	while (!glfwWindowShouldClose(window))
	{
		// check key or mouse events
		glfwPollEvents();

		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		program.use();
		// draw
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(program._program, "u_image"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glUniform1i(glGetUniformLocation(program._program, "u_image2"), 1);

		glUniformMatrix4fv(glGetUniformLocation(program._program, "u_mat"), 1, GL_FALSE, glm::value_ptr(mat));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// swap buffer
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();

	return 0;
}