#include "Shape.h"
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define M_PI 3.14159265358979323846264338327950288

using namespace glm;
using namespace std;

Shape::Shape(Node* nodes, int number, bool solid)
{
	//Catat jumlah vertex yang akan digambar
	numberOfNodes = number;

	//Untuk handle crash pas passing address of array di Shape
	//Ternyata gak perlu tapi
	//glewExperimental = GL_TRUE;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Vector or vec3 untuk posisi pixel
	vector<vec3> vec_pos;
	//pesen memori paling ngk sejumlah input vertex data
	vec_pos.reserve(numberOfNodes);

	//Vector or vec2 untuk texture coordinate
	vector<vec2> vec_textCoord;
	//pesen memori paling ngk sejumlah input vertex data
	vec_textCoord.reserve(numberOfNodes);

	//Convert array vertice yang atributenya vec2 dan vec3
	//Bagi jadi dua vektor
	for (int i = 0; i < numberOfNodes; i++) {
		vec_pos.push_back(nodes[i].getPos());
		vec_textCoord.push_back(nodes[i].getTC());
	}

	glGenBuffers(2, vertexArrayBuffers);

	//Ini buat pos
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[0]);
	//Ganti jadi vektor baru
	glBufferData(GL_ARRAY_BUFFER, numberOfNodes * sizeof(vec_pos[0]), &vec_pos[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	//3 maksudnya x,y,z yang dipake
	//Intinya setting array kita gimana dipakenya sama OpenGL
	int vec3_num = 3;
	glVertexAttribPointer(0, vec3_num, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindVertexArray(0);

	//Increment vertex arraynya, dari 0 jadi 1

	//glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	//Ini buat textCoord
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[1]);
	//Ganti jadi vektor baru
	glBufferData(GL_ARRAY_BUFFER, numberOfNodes * sizeof(vec_textCoord[0]), &vec_textCoord[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	//2 maksudnya cuma x,y yang dipake (vec2)
	//Intinya setting array kita gimana dipakenya sama OpenGL
	int vec2_num = 2;
	glVertexAttribPointer(1, vec2_num, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	//glBindVertexArray(1);

	this->solid = solid;
}

void Shape::Draw() {
	glBindVertexArray(vertexArrayObject);

	//0 artinya dari start
	//numberOfNodes artinya end of reading array (brp banyak vertice)
	//glDrawArrays(GL_TRIANGLES, 0, numberOfNodes);

	if (numberOfNodes == 2) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_LINE_SMOOTH);
		if (!solid) {
			glEnable(GL_LINE_STIPPLE);
		}
		glPushAttrib(GL_LINE_BIT);
		glLineWidth(5);
		glLineStipple(1, 0x00FF);
		glDrawArrays(GL_LINES, 0, numberOfNodes);
		glPopAttrib();
		if (!solid) {
			glDisable(GL_LINE_STIPPLE);
		}
		glPopAttrib();
		glDisable(GL_LINE_SMOOTH);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else if (numberOfNodes == 3) {
		glDrawArrays(GL_TRIANGLES, 0, numberOfNodes);
	}
	else if (numberOfNodes == 4) {
		glDrawArrays(GL_QUADS, 0, numberOfNodes);
	}
	else if (numberOfNodes >= 5) {
		glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfNodes);
	}
	else {
		cerr << "Shape/data input is not recognized" << endl;
	}
}

Shape::~Shape()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}
