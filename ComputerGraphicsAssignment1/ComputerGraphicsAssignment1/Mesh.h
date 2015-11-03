#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using namespace glm;

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec3& col)
	{
		position = pos;
		colour = col;
	}
	Vertex()
	{ }
	vec3 position;
	vec3 colour;
};
class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, GLuint program_ID);
	~Mesh();
	void Draw();
	void Translate(mat4 transformationMatrix);
private:
	enum
	{
		POSITION_VB, COLOUR_VB, NUM_BUFFERS
	};
	GLuint m_VAO;
	GLuint m_VBO[NUM_BUFFERS];
	unsigned int m_drawCount;
	GLuint transformationLocation;
};
#endif //MESH_H
