#include "stdafx.h"
#include "Graphics\GL3Shader.h"

namespace crea
{
	GL3Shader::GL3Shader()
	{
	}

	GL3Shader::~GL3Shader()
	{
		glDeleteProgram(shaderProgram);
	}

	bool GL3Shader::loadFromFile(const string& _name)
	{
		// Read .shader file
		ifstream shaderFile;
		string shaderNames;
		size_t pos = _name.rfind('/');
		string directory = _name.substr(0, ++pos);
		// open files
		shaderFile.open(_name);
		stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderNames = shaderStream.str();
		pos = shaderNames.find('\n');
		string vertexShaderFileName = directory + shaderNames.substr(0, pos);
		string fragmentShaderFileName = directory + shaderNames.substr(pos + 1, string::npos);

		// build and compile our shader program
		// ------------------------------------
		// vertex shader
		ifstream vShaderFile;
		ifstream vertexShaderFile(vertexShaderFileName);
		if (vertexShaderFile.fail())
		{
			cout << "Can't open vertex shader file : " << vertexShaderFileName << std::endl;
			return false;
		}
		//extract .vs code
		stringstream vertexShaderStream;
		string vertexShaderString;
		vertexShaderStream << vertexShaderFile.rdbuf();
		vertexShaderString = vertexShaderStream.str();
		const char* vertexShaderCode = vertexShaderString.c_str();
		vertexShaderFile.close();

		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// fragment shader
		ifstream fragmentShaderFile(fragmentShaderFileName);
		if (fragmentShaderFile.fail())
		{
			cout << "Can't open fragment shader file : " << fragmentShaderFileName << std::endl;
			return false;
		}
		//extract .fs code
		stringstream fragmentShaderStream;
		string fragmentShaderString;
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		fragmentShaderString = fragmentShaderStream.str();
		const char* fragmentShaderCode = fragmentShaderString.c_str();
		fragmentShaderFile.close();

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return true;
	}

	void GL3Shader::use()
	{
		glUseProgram(shaderProgram);
	}

	void GL3Shader::unuse()
	{
		glUseProgram(0);
	}

	// utility uniform functions
	// ------------------------------------------------------------------------
	void GL3Shader::setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void GL3Shader::setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void GL3Shader::setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void GL3Shader::setVec3(const std::string &name, float* vec3) const
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, vec3);
	}
	// ------------------------------------------------------------------------
	void GL3Shader::setMat3(const std::string &name, float* mat3) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, mat3);
	}
	// ------------------------------------------------------------------------
	void GL3Shader::setMat4x4(const std::string &name, float* mat4) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, mat4);
	}
} // namespace Crea