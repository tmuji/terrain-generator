#include <string>

class Shader
{

public:

	int ID;

	Shader(std::string vertexPath, std::string fragmentPath);

	void use();

	void checkCompileErrors(int , std::string type);
};