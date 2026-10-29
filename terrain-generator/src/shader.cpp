#include "../include/shader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glad/gl.h>

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	// file opening
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);

	if (!vertexFile.is_open()) {
		std::cerr << "Could Not Open The Vertex Shader File" << std::endl;
	}

	if (!fragmentFile.is_open()) {
		std::cerr << "Could Not Open The Fragment Shader File" << std::endl;
	}

	std::stringstream vertexStream, fragmentStream;
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	std::string vertexString = vertexStream.str();
	std::string fragmentString = fragmentStream.str();

	const char* vertexSource = vertexString.c_str();
	const char* fragmentSource = fragmentString.c_str();



	// shader creating and program linking
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");


	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");


}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(int typeID, std::string type)
{
	int success;
	char infoLog[1024];
	if (type == "PROGRAM")
	{
		// shader program
		glGetProgramiv(typeID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(typeID, 1024, NULL, infoLog);
			std::cout << "ERROR: SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
		}

	}

	else
	{
		// individual shaders (vertex, fragment)
		glGetShaderiv(typeID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(typeID, 1024, NULL, infoLog);
			std::cout << "ERROR: SHADER " << type << " COMPILATION FAILED\n" << infoLog << std::endl;

		}
	}

}