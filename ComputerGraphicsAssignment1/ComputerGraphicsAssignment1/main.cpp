#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include <sdl2/SDL.h>

using namespace glm;
#undef main
void Left();
void Right();
void Input();
vec3 paddleVel = vec3(0.0);
vec3 paddlePos = vec3(0.0, -0.8, 0.0);

vec3 ballPos = vec3(0.0);
vec3 ballVel = vec3(0.7, 0.3, 0.0);
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Display display(800, 600, "Paddle Ball");
	Shader shader("shader");

	
	
	Vertex paddleVerts[] = { Vertex(vec3(-0.1f, 0.025f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
							 Vertex(vec3(-0.1f, -0.025f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
						     Vertex(vec3(0.1f, -0.025f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
							 Vertex(vec3(-0.1f, 0.025f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
							 Vertex(vec3(0.1f, -0.025f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
							 Vertex(vec3(0.1f, 0.025f, 0.0f), vec3(1.0f, 0.0f, 0.0f)) };
	Vertex ballVerts[] = { Vertex(vec3(-0.05f, 0.05f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
						   Vertex(vec3(-0.05f, -0.05f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
						   Vertex(vec3(0.05f, -0.05f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
						   Vertex(vec3(-0.05, 0.05f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
						   Vertex(vec3(0.05f, -0.05f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
						   Vertex(vec3(0.05f, 0.05f, 0.0f), vec3(0.0f, 1.0f, 0.0f)), };
	
	Mesh paddle(paddleVerts, sizeof(paddleVerts)/sizeof(paddleVerts[0]), shader.GetProgram());
	Mesh ball(ballVerts, sizeof(ballVerts)/sizeof(ballVerts[0]), shader.GetProgram());

	while(!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		shader.Bind();
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
						Left();
						break;
					case SDLK_RIGHT:
						Right();
						break;
					default:
						break;
				}
			}
			
		}
		if(ballPos.x + 0.05f >= 1.0f)
			ballVel = vec3(-ballVel.x, ballVel.y, ballVel.z);
		else if(ballPos.x - 0.05f <= -1.0f)
			ballVel = vec3(-ballVel.x, ballVel.y, ballVel.z);
		if(ballPos.y + 0.05f >= 1.0f)
			ballVel = vec3(ballVel.x, -ballVel.y, ballVel.z);
		else if(ballPos.y - 0.05f <= -1.0f)
			ballVel = vec3(ballVel.x, -ballVel.y, ballVel.z);
		ballPos += ballVel * 1.0f/60.0f;
		ball.Translate(translate(mat4(1.0f), ballPos));
		ball.Draw();
		std::cout << paddleVel.x << std::endl;
		paddlePos += paddleVel * 1.0f/60.0f;
		paddle.Translate(translate(mat4(1.0f), paddlePos));
		paddle.Draw();
		display.Update();
		
	}

	SDL_Quit();
}

void Left()
{
	paddleVel = vec3(-0.1f, 0.0f, 0.0f);
}

void Right()
{
	paddleVel = vec3(0.1f, 0.0f, 0.0f);
}

void Input()
{

}