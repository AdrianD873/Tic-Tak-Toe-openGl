#define GLEW_STATIC

#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Window.h"
#include "Plane.h"
#include "Shader.h"
#include "Texture.h"
#include "Positions.h"

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
	shader.setInt("texture0", 0);
	shader.setInt("texture1", 1);
	shader.setInt("texture1", 1);
	/*****************
	textures
	******************/
	unsigned int texture0 = 0;
	unsigned int texture1 = 0;

	Texture standard(texture0, GL_TEXTURE0, "default.png");
	Texture cross(texture1, GL_TEXTURE1, "cross.png");
	Texture circle(texture1, GL_TEXTURE1, "circle.png");

	/*****************
	positions
	******************/
	standard.bind();
	

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
		Plane topM(one, five, six, two);
		Plane topR(two, six, seven, three);
		Plane middleL(four, eight, nine, five);
		Plane middleM(five, nine, ten, six);
		Plane middleR(six, ten, eleven, seven);
		Plane bottomL(eight, twelve, thirteen, nine);
		Plane bottomM(nine, thirteen, fourteen, ten);
		Plane bottomR(ten, fourteen, fifteen, eleven);


		circle.bind();
		topL.disableColor();
		topL.draw();
		topM.disableColor();
		topM.draw();
		topR.disableColor();
		topR.draw();
		middleL.disableColor();
		middleL.draw();
		middleM.disableColor();
		middleM.draw();
		middleR.disableColor();
		middleR.draw();

		cross.bind();
		bottomL.disableColor();
		bottomL.draw();
		bottomM.disableColor();
		bottomM.draw();
		bottomR.disableColor();
		bottomR.draw();


		cross.unBind();
		circle.unBind();

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