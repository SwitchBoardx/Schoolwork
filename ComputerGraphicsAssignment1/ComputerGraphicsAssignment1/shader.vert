#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColour;

out vec4 Colour;

uniform mat4 TransformationMatrix;

void main()
{
	Colour = vec4(vColour, 1.0f);
	gl_Position = TransformationMatrix * vec4(vPosition, 1.0f);
}