#include <cstdio>
#include <cstdlib>

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

void error_callback(int error, const char* description)
{
	std::fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, const char* argv[])
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) 
	{
		return EXIT_FAILURE;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}