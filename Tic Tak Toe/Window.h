#include <glfw3.h>
#include <iostream>

#ifndef _WINDOW_H_
#define _WINDOW_H_
#endif

class Window
{
private:
	const char* windowName;


public:
	int windowWidth;
	int windowHeight;

	GLFWwindow* window;
	bool closed = false;

	void createWindow(int width = 800, int height = 600, const char* name = "no name")
	{
		windowWidth = width;
		windowHeight = height;
		windowName = name;
		window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "ERROR: faild to initialize window: " << windowName << std::endl;
			glfwTerminate();
		}

		glViewport(0, 0, windowWidth, windowHeight);
	}

	void processInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	int getWindowHeight()
	{
		return windowHeight;
	}

	int getWinodwWidth()
	{
		return windowWidth;
	}
};