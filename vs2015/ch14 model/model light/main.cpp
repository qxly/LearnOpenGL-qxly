#define GLEW_STATIC
// glew
#include "GL/glew.h"
// glfw
#include "GLFW/glfw3.h"
// SOIL
#include "SOIL/SOIL.h"

//GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "../../../dep/lib_x86/debug_static/glew32sd.lib")
#pragma comment(lib, "../../../dep/lib_x86/debug_static/glfw3.lib")
#pragma comment(lib, "../../../dep/lib_x86/debug_static/SOIL.lib")

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>
#include <direct.h>

bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool firstMouse = true;
GLfloat lastX = 400.0f;
GLfloat lastY = 300.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

// key callback function
void key_callback(GLFWwindow* window, int	key, int scancode, int acion, int mode)
{
	if (key == GLFW_KEY_ESCAPE && acion == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key <= 1024)
	{
		if (acion == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (acion == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);


	// game loop
	char buf[1000];
	_getcwd(buf, 1000);
	std::string workDir = buf;

	std::string model_vs = workDir + "/model.vs";
	std::string model_frag = workDir + "/model.frag";
	Shader shader(model_vs.c_str(), model_frag.c_str());

	// Load models
	std::string modelDir = workDir + "/nanosuit/nanosuit.obj";
	Model modelObj((GLchar*)modelDir.c_str());

	glEnable(GL_DEPTH_TEST);

	// Point light positions
	glm::vec3 pointLightPositions[] = {
		glm::vec3(2.3f, -1.6f, -3.0f),
		glm::vec3(-1.7f, 0.9f, 1.0f)
	};

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// check key or mouse events
		glfwPollEvents();
		do_movement();

		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		
		shader.use();   // <-- Don't forget this one!
						// Transformation matrices
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Set the lighting uniforms
		glUniform3f(glGetUniformLocation(shader.program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Point light 1
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform1f(glGetUniformLocation(shader.program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(shader.program, "pointLights[0].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(shader.program, "pointLights[0].quadratic"), 0.0f);
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		// Point light 2
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform1f(glGetUniformLocation(shader.program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(shader.program, "pointLights[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(shader.program, "pointLights[1].quadratic"), 0.0f);
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader.program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);


		// Draw the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		modelObj.draw(shader);
		
		// swap buffer
		glfwSwapBuffers(window);
	}

	glDisable(GL_DEPTH_TEST);
	glfwTerminate();

	return 0;
}