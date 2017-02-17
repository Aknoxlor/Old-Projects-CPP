
#include "stdafx.h"
#include "SB_Shader.h"
#include "SB_Math.h"
#include "LoopEngine.h"

void LoopEngine::start(void)
{
	std::srand((unsigned int)std::time(NULL));

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 3;

	_mainWindow.create(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	glewInit();

	fprintf(stderr, "%i%i\n", _mainWindow.getSettings().majorVersion, _mainWindow.getSettings().minorVersion);

	initVertexBuffer();
	initShader();

	while(!_isExiting)
	{
		loop();
	}

	_mainWindow.close();
	delete _shader;
}

void LoopEngine::initVertexBuffer()
{
const float vertexData[] = 
	{
     0.0f,    0.3f, 0.0f, 1.0f,
     0.3f, -0.200f, 0.0f, 1.0f,
    -0.3f, -0.200f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &_positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, _positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void LoopEngine::initShader()
{
	const std::string vertexShader
	(
		"#version 430\n"
		"layout(location = 0) in vec4 position;\n"
		"uniform vec2 offset;\n"
		"void main()\n"
		"{\n"
		"   vec4 totalOffset = vec4(offset.x, offset.y, 0.0f, 0.0f);\n"
		"	gl_Position = totalOffset + position;\n"
		"}\n"
	);

const std::string fragmentShader
	(
		"#version 430\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"	outputColor = vec4(1.0f,1.0f,1.0f,1.0f);\n"
		"}\n"
	);

	_shader = new SB_Shader(vertexShader, fragmentShader);
	_offsetRef = glGetUniformLocation(_shader->getAddress(), "offset");
}



void LoopEngine::loop()
{
	float timePos = _frameClock.getElapsedTime().asMilliseconds() / 1000.0f;
	timePos = fmodf(timePos, 5.0f);
	sf::Vector2f path = GMath::CreateVector(0.5,72 * timePos);
	//adjustVertexData(path);

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->bind();
	glUniform2f(_offsetRef, path.x, path.y);

	glBindBuffer(GL_ARRAY_BUFFER, _positionBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	_shader->unbind();

	_mainWindow.display();

	sf::Event currentEvent;
	while(_mainWindow.pollEvent(currentEvent))
	{
		if(currentEvent.type == sf::Event::Closed)
		{
			_isExiting = true;
		}

		if(currentEvent.type == sf::Event::Resized)
		{
			glViewport(0, 0, currentEvent.size.width, currentEvent.size.height);
		}
	}
}

void LoopEngine::adjustVertexData(sf::Vector2f path)
{
	/*
	std::vector<float> fNewData(ARRAY_COUNT(vertexData));
	memcpy(&fNewData[0], vertexPositions, sizeof(vertexPositions));

	for(int iVertex = 0; iVertex < ARRAY_COUNT(vertexPositions); iVertex += 4)
	{
		fNewData[iVertex] += fXOffset;
		fNewData[iVertex + 1] += fYOffset;
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &fNewData[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
}

//Intilizations
bool LoopEngine::_isExiting = false;

sf::Window LoopEngine::_mainWindow;
sf::Clock LoopEngine::_frameClock;
GLuint LoopEngine::_positionBufferObject = 0;
GLuint LoopEngine::_vao = 0;
GLuint LoopEngine::_offsetRef = 0;
SB_Shader* LoopEngine::_shader = NULL;