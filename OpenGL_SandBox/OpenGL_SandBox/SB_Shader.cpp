#include "stdafx.h"
#include "SB_Shader.h"

SB_Shader::SB_Shader(const std::string &vertexFile, const std::string &fragmentFile)
{
	_address = glCreateProgram();

	const char *vertexData = vertexFile.c_str();
	const char *fragmentData = fragmentFile.c_str();

	_vertexShader = compile(GL_VERTEX_SHADER, vertexData);
	_fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentData);

	glLinkProgram(_address);

	GLint status;
	glGetProgramiv (_address, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(_address, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(_address, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Compile failure in shader:\n%s\n", strInfoLog);
		abort();
	}
}

SB_Shader::~SB_Shader()
{
	glDetachShader(_address, _vertexShader);
    glDetachShader(_address, _fragmentShader);
    
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
    glDeleteProgram(_address);
}

void SB_Shader::bind()
{
	glUseProgram(_address);
}

void SB_Shader::unbind()
{
	glUseProgram(0);
}

GLuint SB_Shader::getAddress()
{
	return _address;
}

GLuint SB_Shader::compile(GLenum shaderType, const char *fileData)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &fileData, NULL);
	glCompileShader(shader);
    
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Compile failure in shader:\n%s\n", strInfoLog);
		abort();
	}

	glAttachShader(_address, shader);

	return shader;
}