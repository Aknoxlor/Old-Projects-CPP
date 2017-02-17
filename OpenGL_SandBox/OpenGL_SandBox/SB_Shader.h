#pragma once

class SB_Shader
{
public:
	SB_Shader(const std::string &vertexFile, const std::string &fragmentFile);
	~SB_Shader();

	void bind();
	void unbind();

	GLuint getAddress();

private:
	GLuint compile(GLenum shaderType, const char *fileData);

	GLuint _address;
	GLuint _vertexShader;
	GLuint _fragmentShader;

};