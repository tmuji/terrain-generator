#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


const char* vertex = "#version 330 core\n"
"\n"
"// Input vertex data from the Vertex Buffer Object (VBO)\n"
"layout (location = 0) in vec3 aPos; \n"
"\n"
"// Output variable that will be sent to the fragment shader\n"
"out vec4 vertexColor; \n"
"\n"
"void main()\n"
"{\n"
"    // gl_Position is a built-in OpenGL variable that sets the final vertex position\n"
"    gl_Position = vec4(aPos, 1.0); \n"
"    \n"
"    // Assign a default orange/red color vector (RGBA) to pass down the pipeline\n"
"    vertexColor = vec4(1.0, 0.5, 0.0, 1.0); \n"
"}\n"
"";

const char* fragment = "#version 330 core\n"
"\n"
"// Input variable from the vertex shader (must match name and type exactly)\n"
"in vec4 vertexColor;\n"
"\n"
"// The final output color vector for this pixel/fragment\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    // Set the pixel color to match the color received from the vertex shader\n"
"    FragColor = vertexColor;\n"
"}\n"
"";


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

	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	while(!glfwWindowShouldClose(window))
	{

		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		// main loop
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
	

	// clean up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
