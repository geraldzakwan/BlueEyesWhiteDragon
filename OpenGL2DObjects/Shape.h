#ifndef SHAPE_H
#define SHAPE_H

#include "Node.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

#pragma once

class Shape
{
public:
	Shape(Node*, int, bool);
	void Draw();
	~Shape();

private:
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[2];
	int numberOfNodes;

	bool solid;
};

#endif //SHAPE2D_H

