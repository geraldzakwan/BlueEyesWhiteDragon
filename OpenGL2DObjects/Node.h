#ifndef NODE_H
#define NODE_H
#pragma once
#include <glm/glm.hpp>
using namespace glm;

//Coordinates between -1 and 1

class Node
{
public:
	//Node(const vec3&, const vec2&);
	Node(const vec3& position = vec3(), const vec2& textCoord = vec2()) {
		pos = position;
		textureCoordinate = textCoord;
	}

	//Getter pos
	vec3 getPos();

	//Getter text coordinate
	vec2 getTC();

	//Setter
	void setEverything(const vec3&, const vec2&);

private:
	//Ini cuma posisi aja, x,y,z coordinate blom color ato texture
	vec3 pos;
	//Ini buat setting coordinate texture yg dipake
	vec2 textureCoordinate;
};

#endif

