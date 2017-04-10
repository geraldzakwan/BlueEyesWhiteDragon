#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
using namespace std;

class Texture
{
public:
	Texture(const string&);
	void Bind();

	virtual ~Texture();
protected:
private:
	GLuint tekstur;
};

#endif