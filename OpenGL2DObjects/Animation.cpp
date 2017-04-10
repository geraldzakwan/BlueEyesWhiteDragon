#include "Animation.h"
using namespace glm;

mat4 Animation::GetAnimationMatrix() const {
	//buat matrix 4x4 untuk representasi posisi
	mat4 pos_matrix = translate(pos);
	//buat matrix 4x4 untuk representasi scale
	mat4 scale_matrix = scale(scl);
	//ada isu gimble lock klo pake representasi rotasi pake vektor
	//pake quaternion lebih bagus
	mat4 x_matrix = rotate(rot.x, vec3(1.0, 0.0, 0.0));
	mat4 y_matrix = rotate(rot.y, vec3(0.0, 1.0, 0.0));
	mat4 z_matrix = rotate(rot.z, vec3(0.0, 0.0, 1.0));
	mat4 rot_matrix = x_matrix * y_matrix * z_matrix;

	//Urutan perkalian matrixnya ngaruh kaya pelajaran transformasi SMA
	//Kita pengen transformasinya :
	//1. Ukuran dulu diubah
	//2. Baru diputer
	//3. Baru digeser posisinya
	//Maka, transform matrixnya ya kaya gini :
	return pos_matrix * rot_matrix * scale_matrix;
}

vec3 Animation::GetPos() { 
	return pos; 
}

vec3 Animation::GetRot() { 
	return rot; 
}
vec3 Animation::GetScale() { 
	return scl; 
}

void Animation::SetPos_X(const GLfloat& pos_x) {
	pos.x = pos_x;
}

void Animation::SetPos_Y(const GLfloat& pos_y) {
	pos.y = pos_y;
}

void Animation::SetPos_Z(const GLfloat& pos_z) {
	pos.z = pos_z;
}

void Animation::SetRot_X(const GLfloat& rot_x) {
	rot.x = rot_x;
}

void Animation::SetRot_Y(const GLfloat& rot_y) {
	rot.y = rot_y;
}

void Animation::SetRot_Z(const GLfloat& rot_z){
	rot.z = rot_z;
}

void Animation::SetScale(const vec3& scale) { 
	scl = scale; 
}