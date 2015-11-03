#include "Mesh.h"


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, GLuint programID)
{
	m_drawCount = numVertices;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(NUM_BUFFERS, m_VBO);
	std::vector<vec3> positions;
	std::vector<vec3> colours;
	positions.reserve(numVertices);
	colours.reserve(numVertices);
	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].position);
		colours.push_back(vertices[i].colour);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glBindAttribLocation(programID, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(colours[0]), &colours[0], GL_STATIC_DRAW);
	glBindAttribLocation(programID, 1, "vColour");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	transformationLocation = glGetUniformLocation(programID, "TransformationMatrix");

	
}

void Mesh::Draw()
{
	glBindVertexArray(m_VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{

}

void Mesh::Translate(mat4 transformMatrix)
{
	glBindVertexArray(m_VAO);
	glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, &transformMatrix[0][0]);
	glBindVertexArray(0);
}