#include <glm.hpp>
#include <glew.h>

#define _PLANE_H_


class Plane
{
private:
	glm::fvec3 vertices[12] = {
	 topLeft, topLeftCol, glm::vec3(0.f, 1.f, 0.f),
	 bottomLeft, bottomLeftCol, glm::vec3(0.f, 0.f, 0.f),
	 bottomRight, bottomRightCol, glm::vec3(1.f, 0.f, 0.f),
	 topRight, topRightCol, glm::vec3(1.f, 1.f, 0.f)
	};
	unsigned int indices[6]{
		1, 0, 2,
		2, 0, 3
	};

	glm::fvec3 topLeft, bottomLeft, bottomRight, topRight, topLeftCol, bottomLeftCol, bottomRightCol, topRightCol;

	unsigned int vao;
	unsigned int vbo;


public:

	Plane(
			glm::fvec3 topL = glm::fvec3(-0.5f, 0.5f, 0.f),
			glm::fvec3 bottomL = glm::fvec3(-0.5f, -0.5f, 0.f),
			glm::fvec3 bottomR = glm::fvec3(0.5f, -0.5f, 0.f),
			glm::fvec3 topR = glm::fvec3(0.5f, 0.5f, 0.f),
			glm::fvec3 topLCol = glm::fvec3(1.f, 0.f, 0.f),
			glm::fvec3 bottomLCol = glm::fvec3(0.f, 1.f, 0.f),
			glm::fvec3 bottomRCol = glm::fvec3(0.f, 0.f, 1.f),
			glm::fvec3 topRCol = glm::fvec3(1.f, 1.f, 1.f)
		)
	{
		topLeft = topL;
		bottomLeft = bottomL;
		bottomRight = bottomR;
		topRight = topR;
		topLeftCol = topLCol;
		bottomLeftCol = bottomLCol;
		bottomRightCol = bottomRCol;
		topRightCol = topRCol;

		glGenVertexArrays(1, &vao);

		//create vertex buffer object (allocate memory on gpu)
		glGenBuffers(1, &vbo);

		//bind objects
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//send data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/*intepretation of data 0 = Position of the data send to -> see vertex Shader
								3 = number of Positions of one triangle / number of Texture coords
								GL_FLOAT = Type of date send
								FL_FALSE = don't normalize data
								3*sizeof(float) = space to the next position (1Position = floatX + floatY + floatZ)
								(void*)0  = start of the data (type void* requred)*/
		//positon
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 3) * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 3) * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 3) * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//dnable vertex data send (0 = Position of the Data -> specified by glVertexAttribPointer)
		glBindBuffer(1, 0);
	}

	~Plane()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	void draw()
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);
	}

	void setPosition(
		glm::fvec3 topL,
		glm::fvec3 bottomL,
		glm::fvec3 bottomR,
		glm::fvec3 topR)
	{
		topLeft = topL;
		bottomLeft = bottomL;
		bottomRight = bottomR;
		topRight = topR;
	}

	void setColor(glm::fvec3 topLCol, glm::fvec3 bottomLCol, glm::fvec3 bottomRCol,	glm::fvec3 topRCol)
	{
		topLeftCol = topLCol;
		bottomLeftCol = bottomLCol;
		bottomRightCol = bottomRCol;
		topRightCol = topRCol;
	}

	void setColor(glm::vec3 color)
	{
		topLeftCol = color;
		bottomLeftCol = color;
		bottomRightCol = color;
		topRightCol = color;
	}

	void disableColor()
	{
		glBindVertexArray(vao);
		glDisableVertexAttribArray(1);
	}

	void anableColor()
	{
		glBindVertexArray(vao);
		glEnableVertexAttribArray(1);
	}

	void disableTexture()
	{
		glBindVertexArray(vao);
		glDisableVertexAttribArray(2);
	}

	void enableTexture()
	{
		glBindVertexArray(vao);
		glEnableVertexAttribArray(2);
	}
};