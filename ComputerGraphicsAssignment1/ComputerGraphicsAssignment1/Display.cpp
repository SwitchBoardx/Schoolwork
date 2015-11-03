#include "Display.h"
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
	

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum err = glewInit();
	if(err != GLEW_OK)
		std::cerr << "Glew failed to init" << std::endl;

	m_isClosed = false;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
bool Display::IsClosed()
{
	return m_isClosed;
}
Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);
}

void Display::SetClosed(bool closed)
{
	m_isClosed = closed;
}