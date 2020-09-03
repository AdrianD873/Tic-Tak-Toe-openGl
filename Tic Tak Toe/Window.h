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

	int getWindowHeight()
	{
		return windowHeight;
	}

	int getWinodwWidth()
	{
		return windowWidth;
	}
};