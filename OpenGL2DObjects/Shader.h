#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <string>
#include <GL/glew.h>
#include "Animation.h"
using namespace std;

class Shader
{
public:
	Shader(const string& fileName);

	void Bind();
	void Update(const Animation&);

	virtual ~Shader();
protected:
private:

	GLuint arsiranArray[2];
	GLuint prog;
	GLuint transform;
};

#endif