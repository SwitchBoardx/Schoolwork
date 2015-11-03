#include "Shader.h"
#include <fstream>
#include <iostream>
#include <vector>

static GLuint CreateShader(const std::string& text, GLenum shaderType);
static std::string LoadShader(const std::string& fileName);
static void CheckShaderStatus(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);

Shader::Shader(std::string fileName)
{
	m_programID = glCreateProgram();

	m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < 2; i++)
		glAttachShader(m_programID, m_shaders[i]);

	glLinkProgram(m_programID);
	CheckShaderStatus(m_programID, GL_LINK_STATUS, true, "Program Linking failed: ");

	glValidateProgram(m_programID);
	CheckShaderStatus(m_programID, GL_VALIDATE_STATUS, true, "Program invalid: ");
}
GLuint Shader::GetProgram()
{
	return m_programID;
}

Shader::~Shader(void)
{
	for(unsigned int i = 0; i < 2; i++)
	{
		glDetachShader(m_programID, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_programID);
}

void Shader::Bind()
{
	glUseProgram(m_programID);
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file(fileName.c_str());

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
		std::cerr << "Unable to load shader: " + fileName << std::endl;
	return output;
}

static void CheckShaderStatus(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg)
{
	GLint success = 0;

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		if(isProgram)
		{
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			char* infoLog = new char[maxLength];
			glGetProgramInfoLog(shader, maxLength, &maxLength, infoLog);
			std::cerr << errorMsg + std::string(infoLog) << std::endl;
			delete infoLog;
		}
		else
		{
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);
			std::cerr << errorMsg + std::string(infoLog) << std::endl;
			delete infoLog;
		}
	}
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if(shader == 0)
		std::cerr << "Shader creation failed" << std::endl;

	const GLchar* shaderString[1];
	GLint ShaderStringLength[1];
	shaderString[0] = text.c_str();
	ShaderStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderString, ShaderStringLength);
	glCompileShader(shader);

	CheckShaderStatus(shader, GL_COMPILE_STATUS, false, "Shader not compiled: ");

	return shader;
}