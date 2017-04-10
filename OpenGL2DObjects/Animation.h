#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h> //cuma untuk GLfloat aja sih sebenernya

using namespace glm;

class Animation
{
public:
	Animation(const vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) {
		//Defaultnya pos sama rot vec kosong aja
		//Kalo scale jgn kosong ntar ngk ada gambar, kasi aja 1
		pos = position;
		rot = rotation;
		scl = scale;
	}
	
	//4x4 transform matrix
	mat4 GetAnimationMatrix() const;

	//Getter
	vec3 GetPos();
	vec3 GetRot();
	vec3 GetScale();

	//Setter
	void SetPos_X(const GLfloat&);
	void SetPos_Y(const GLfloat&);
	void SetPos_Z(const GLfloat&);

	void SetRot_X(const GLfloat&);
	void SetRot_Y(const GLfloat&);
	void SetRot_Z(const GLfloat&);

	void SetScale(const vec3&);

protected:
private:
	vec3 pos;
	vec3 rot;
	vec3 scl;
};

#endif //ANIMATION_H
