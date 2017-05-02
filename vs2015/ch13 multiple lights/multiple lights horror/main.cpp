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
#include "camera.h"

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

	 //vertex data
	GLfloat vertices[] = {
		// Positions           // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	// Positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {
		glm::vec3(0.1f, 0.1f, 0.1f),
		glm::vec3(0.1f, 0.1f, 0.1f),
		glm::vec3(0.1f, 0.1f, 0.1f),
		glm::vec3(0.3f, 0.1f, 0.1f)
	};

	// gen VAO
	GLuint objectVAO;
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

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

	glBindVertexArray(0);

	// vao2
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Gen texture
	GLuint texdiff;
	glGenTextures(1, &texdiff);
	glBindTexture(GL_TEXTURE_2D, texdiff);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int image_w, image_h;
	unsigned char* image = SOIL_load_image("container2.png", &image_w, &image_h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// gen texture specular
	GLuint texspecular;
	glGenTextures(1, &texspecular);
	glBindTexture(GL_TEXTURE_2D, texspecular);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image("container2_specular.png", &image_w, &image_h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// game loop
	char buf[1000];
	_getcwd(buf, 1000);
	std::string fileDir = buf;

	std::string objectvs = fileDir + "/object.vs";
	std::string objectfrag = fileDir + "/object.frag";
	//Shader object(fileDir + "/object.vs", fileDir + "/object.frag");
	std::string lightvs = fileDir + "/light.vs";
	std::string lightfrag = fileDir + "/light.frag";
	Shader object(objectvs.c_str(), objectfrag.c_str());
	//Shader light(fileDir + "/light.vs", fileDir + "/light.frag");
	Shader light(lightvs.c_str(), lightfrag.c_str());	

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// check key or mouse events
		glfwPollEvents();
		do_movement();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		
		glm::vec3 lightColor(1.0, 1.0, 1.0);
		//lightColor.x = sin(glfwGetTime() * 0.2);
		//lightColor.y = sin(glfwGetTime() * 0.07);
		//lightColor.z = sin(glfwGetTime() * 0.13);

		//glm::vec3 ambientColor = lightColor * glm::vec3(0.2);
		//glm::vec3 diffuseColor = lightColor * glm::vec3(0.5);		
		glm::vec3 ambientColor(0.2, 0.2, 0.2);
		glm::vec3 diffuseColor(0.5, 0.5, 0.5);

		// draw object
		object.use();
		glBindVertexArray(objectVAO);
		glm::mat4 model;
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 proj;
		proj = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		
		glUniform3fv(glGetUniformLocation(object._program, "viewPos"), 1, glm::value_ptr(camera.Position));

		//glUniform3f(glGetUniformLocation(object._program, "material.ambient"), 1.0, 0.5, 0.31);
		//glUniform3f(glGetUniformLocation(object._program, "material.diffuse"), 1.0, 0.5, 0.31);
		//glUniform3f(glGetUniformLocation(object._program, "material.specular"), 0.5, 0.5, 0.5);
		glUniform1i(glGetUniformLocation(object._program, "material.diffuse"), 0);		
		glUniform1i(glGetUniformLocation(object._program, "material.specular"), 1);
		glUniform1f(glGetUniformLocation(object._program, "material.shininess"), 32.0);
		
		// Directional light

		glUniform3f(glGetUniformLocation(object._program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);

		glUniform3f(glGetUniformLocation(object._program, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);

		glUniform3f(glGetUniformLocation(object._program, "dirLight.diffuse"), 0.05f, 0.05f, 0.05);

		glUniform3f(glGetUniformLocation(object._program, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
		// Point light 1

		glUniform3f(glGetUniformLocation(object._program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[0].ambient"), pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[0].constant"), 1.0f);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[0].linear"), 0.14);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[0].quadratic"), 0.07);
		// Point light 2

		glUniform3f(glGetUniformLocation(object._program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[1].ambient"), pointLightColors[1].x * 0.1, pointLightColors[1].y * 0.1, pointLightColors[1].z * 0.1);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[1].constant"), 1.0f);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[1].linear"), 0.14);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[1].quadratic"), 0.07);
		// Point light 3

		glUniform3f(glGetUniformLocation(object._program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[2].ambient"), pointLightColors[2].x * 0.1, pointLightColors[2].y * 0.1, pointLightColors[2].z * 0.1);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[2].constant"), 1.0f);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[2].linear"), 0.22);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[2].quadratic"), 0.20);
		// Point light 4

		glUniform3f(glGetUniformLocation(object._program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[3].ambient"), pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);

		glUniform3f(glGetUniformLocation(object._program, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[3].constant"), 1.0f);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[3].linear"), 0.14);

		glUniform1f(glGetUniformLocation(object._program, "pointLights[3].quadratic"), 0.07);
		// SpotLight

		glUniform3f(glGetUniformLocation(object._program, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);

		glUniform3f(glGetUniformLocation(object._program, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);

		glUniform3f(glGetUniformLocation(object._program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);

		glUniform3f(glGetUniformLocation(object._program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);

		glUniform3f(glGetUniformLocation(object._program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);

		glUniform1f(glGetUniformLocation(object._program, "spotLight.constant"), 1.0f);

		glUniform1f(glGetUniformLocation(object._program, "spotLight.linear"), 0.09);

		glUniform1f(glGetUniformLocation(object._program, "spotLight.quadratic"), 0.032);

		glUniform1f(glGetUniformLocation(object._program, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));

		glUniform1f(glGetUniformLocation(object._program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texdiff);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texspecular);

		for (int i = 0; i < 10; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0 * i;
			model = glm::rotate(model, angle, glm::vec3(1.0, 0.3, 0.5));
			glm::mat4 mat = proj * view * model;
			glUniformMatrix4fv(glGetUniformLocation(object._program, "u_mat"), 1, GL_FALSE, glm::value_ptr(mat));
			glUniformMatrix4fv(glGetUniformLocation(object._program, "u_matModel"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// draw light
		light.use();
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			proj = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
			glm::mat4 matLight = proj * view * model;
			glUniformMatrix4fv(glGetUniformLocation(light._program, "u_mat"), 1, GL_FALSE, glm::value_ptr(matLight));
			glUniform3fv(glGetUniformLocation(light._program, "u_lightColor"), 1, glm::value_ptr(lightColor));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		
		glBindVertexArray(0);

		// swap buffer
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &objectVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDisable(GL_DEPTH_TEST);

	glfwTerminate();

	return 0;
}