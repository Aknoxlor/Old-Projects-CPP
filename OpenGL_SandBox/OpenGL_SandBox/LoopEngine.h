#pragma once
#include "SB_Shader.h"

class LoopEngine
{
public:
	static void start();

	const static int SCREEN_WIDTH = 800; // 512 * 1.5
	const static int SCREEN_HEIGHT = 600; // 384 * 1.5

private:
	static void initVertexBuffer();
	static void initShader();
	static void loop();

	static void adjustVertexData(sf::Vector2f path);
  
	static bool _isExiting;

	static sf::Clock _frameClock;
	static sf::Window _mainWindow;

	static GLuint _positionBufferObject;
	static GLuint _vao;
	static GLuint _offsetRef;

	static SB_Shader *_shader;
};