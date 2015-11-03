#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader(const std::string fileName);
	virtual ~Shader();
	void Bind();
	GLuint GetProgram();
	GLuint m_programID;
	GLuint m_shaders[2];
};
#endif //SHADER_H
