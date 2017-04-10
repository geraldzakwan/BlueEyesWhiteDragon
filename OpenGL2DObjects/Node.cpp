#include "Node.h"

//Getter pos
vec3 Node::getPos() {
	return pos;
}

//Getter text coordinate
vec2 Node::getTC() {
	return textureCoordinate;
}

void Node::setEverything(const vec3& position, const vec2& TC) {
	pos = position;
	textureCoordinate = TC;
}