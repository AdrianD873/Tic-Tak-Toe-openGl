#define GLEW_STATIC

#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Window.h"
#include "Plane.h"
#include "Shader.h"
#include "Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window mainWindow;

int main()
{
	/*****************
	initialize glfw
	*****************/
	bool  status = glfwInit();
	if (status == GLFW_TRUE)
		std::cout << "glfw initialized" << std::endl;
	else
		std::cout << "initialization of glfw failed" << std::endl;

	/*******************
	openGl setup
	*******************/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	std::cout << "using GLFW 4.4" << std::endl;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//using only modern OpenGl functions

	/*****************
	create a window
	******************/
	mainWindow.createWindow(600, 600, "window 0");

	glfwMakeContextCurrent(mainWindow.window);
	/*****************
	initialize Glew
	******************/
	if (glewInit() == GLEW_OK)
		std::cout << "glew initialized" << std::endl;
	else
	{
		std::cout << "glew initialization failed" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(mainWindow.window, framebuffer_size_callback);

	/*****************
	Shader
	******************/
	Shader shader = Shader("VertexShader.glsl", "FragmentShader.glsl");
	shader.use();

	/*****************
	textures
	******************/
	unsigned int texture0 = 0;
	unsigned int texture1 = 0;
	unsigned int texture2 = 0;

	Texture standard(texture0, GL_TEXTURE0, "default.png");
	standard.bind();

	/*****************
	positions
	******************/
	glm::vec3 zero = glm::vec3(-1.f, 1.f, 0.f);
	glm::vec3 one = glm::vec3(-(1.f - (2.f / 3.f)), 1.f, 0.f);
	glm::vec3 two = glm::vec3(1.f - (2.f / 3.f), 1.f, 0.f);
	glm::vec3 three = glm::vec3(1.f, 1.f, 0.f);
	glm::vec3 four = glm::vec3(-1.f, 1.f - (2.f / 3.f), 0.f);
	glm::vec3 five = glm::vec3(-(1.f - (2.f / 3.f)), 1.f - (2.f / 3.f), 0.f);

	while (!glfwWindowShouldClose(mainWindow.window))
	{
		glfwMakeContextCurrent(mainWindow.window);
		/*****************
		input
		******************/
		mainWindow.processInput();

		/*****************
		rendering
		******************/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Plane topL(zero, four, five, one);
		topL.disableColor();
		topL.draw();

		glfwSwapBuffers(mainWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();
	std::cout << "the program has ended" << std::endl;
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwMakeContextCurrent(mainWindow.window);
	glViewport(0, 0, width, height);
	mainWindow.windowWidth = width;
	mainWindow.windowHeight = height;
}