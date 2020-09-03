#define GLEW_STATIC

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Plane.h"
#include "Shader.h"
#include "Texture.h"
#include "Positions.h"
#include "Input.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);

Window mainWindow;

int states[] = {0, 0, 0,
				0, 0, 0,
				0, 0, 0};

int turn = 1;

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
	setup
	******************/
	standard.bind();
	glfwMakeContextCurrent(mainWindow.window);
	glfwSetMouseButtonCallback(mainWindow.window, mouseButtonCallback);

	while (!glfwWindowShouldClose(mainWindow.window))
	{
		/*****************
		input
		******************/
		processKeyInput(mainWindow.window);

		/*****************
		rendering
		******************/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Plane field(zero, four, five, one);
		field.disableColor();

		glm::fvec3 offset(0.f);

		int pos = glGetUniformLocation(shader.ID, "offset");

		for (int i = 0; i <= 8; i++)
		{
			cross.unBind();	//unbindes cross and circle
			if (i == 0)
			{
				offset = glm::fvec3(0.f);
			}
			else if (i == 1)
			{
				offset = glm::fvec3(1.f - (1.f / 3.f), 0.f, 0.f);

			}
			else if(i == 2)
			{
				offset = glm::fvec3(2.f - (2.f / 3.f), 0.f, 0.f);
			}
			else if (i == 3)
			{
				offset = glm::fvec3(0.f, -(1.f - (1.f / 3.f)), 0.f);
			}
			else if (i == 4)
			{
				offset = glm::fvec3(1.f - (1.f / 3.f), -(1.f - (1.f / 3.f)), 0.f);
			}
			else if (i == 5)
			{
				offset = glm::fvec3(2.f - (2.f / 3.f), -(1.f - (1.f / 3.f)), 0.f);
			}
			else if (i == 6)
			{
				offset = glm::fvec3(0.f, -(2.f - (2.f / 3.f)), 0.f);
			}
			else if (i == 7)
			{
				offset = glm::fvec3(1.f - (1.f / 3.f), -(2.f - (2.f / 3.f)), 0.f);
			}
			else if (i == 8)
			{
				offset = glm::fvec3(2.f - (2.f / 3.f), -(2.f - (2.f / 3.f)), 0.f);
			}

			if (states[i] == 1)
				cross.bind();
			else if (states[i] == 2)
				circle.bind();

			glUniform3fv(pos, 1, glm::value_ptr(offset));
			field.draw();
		}

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

void markField()
{
	double xpos, ypos;
	int height = mainWindow.getWindowHeight();
	int width = mainWindow.getWinodwWidth();
	glfwGetCursorPos(mainWindow.window, &xpos, &ypos);
	std::cout << "pos: x." << xpos << " y." << ypos << std::endl;

	if (xpos < width / 3)
	{
		if (ypos < height / 3)
			states[0] = turn;
		else if (ypos > 2 * height / 3)
			states[6] = turn;
		else
			states[3] = turn;
	}
	else if (xpos > 2 * width / 3)
	{
		if (ypos < height / 3)
			states[2] = turn;
		else if (ypos > 2 * height / 3)
			states[8] = turn;
		else
			states[5] = turn;
	}
	else
	{
		if (ypos < height / 3)
			states[1] = turn;
		else if (ypos > 2 * height / 3)
			states[7] = turn;
		else
			states[4] = turn;
	}
	
	if (turn == 1)
		turn = 2;
	else
		turn = 1;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
		markField();
}
