#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../include/shader.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;




float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() 
{

	// load glfw
	if (!glfwInit()) {
		std::cerr << "Failed To Initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);





	// create the main window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Terrain Generator", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed To Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// load glad AFTER THE WINDOW CODE
	if (!gladLoadGL(glfwGetProcAddress)) {
		std::cerr << "Failed To Initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}


	unsigned int VAO, VBO;

	// gen and bind vao
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// gen and bind vbo
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// vbo data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// vao data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	

	
	Shader shaderProgram = Shader("../../../../terrain-generator/shaders/vertex.glsl", "../../../../terrain-generator/shaders/fragment.glsl");

	while(!glfwWindowShouldClose(window))
	{

		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		// main loop
		shaderProgram.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
	

	// clean up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
