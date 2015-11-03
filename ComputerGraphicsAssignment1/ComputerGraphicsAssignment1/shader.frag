#version 430 core

out vec4 fColour;
in vec4 Colour;



void main()
{
	fColour = Colour;
}