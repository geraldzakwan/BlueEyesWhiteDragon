#include <iostream>
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glut/glfw3.h>
#include "Shape.h"
#include "Animation.h"
#include <vector>
using namespace std;
using namespace glm;

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 720

Node* buildCircleVerticesArray(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);

int shapeChoices();
string textureChoices();

int main(int argc, char* argv[]) {

	int choice = shapeChoices();
	int numberOfVertices;
	bool solid = true;
	Node* vertices;

	switch (choice) {
		//Garis
		case 1	:	cout << "Input 1 untuk garis solid, 0 untuk putus2" << endl;
					int a;
					do {
						cout << "Input : ";
						cin >> a;
						if ((a != 0) && (a != 1)) {
							cout << "Input salah, 1 untuk solid, 0 untuk putus2" << endl;
						}
					} while ((a != 0) && (a != 1));

					if (a == 0) {
						solid = false;
					} else if (a==1) {
						solid = true;
					}

					numberOfVertices = 2;
					vertices = new Node[2];
					vertices[0].setEverything(vec3(-0.5, -0.5, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(0.5, 0.5, 0.0), vec2(0.0, 1.0));
					break;
		//Segitiga sama kaki
		case 2	:	numberOfVertices = 3;
					vertices = new Node[3];
					//Buat vec2 kan dia textCoord, kalo misal segitiga ya ambil bentuk segitiga dari texturenya
					//Kiri bawah (0,0)
					//Atas tengah (0.5,1)
					//Kanan bawah (1,0)
					vertices[0].setEverything(vec3(-0.5, -0.4, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(0.0, 0.4, 0.0), vec2(0.5, 1.0));
					vertices[2].setEverything(vec3(0.5, -0.4, 0.0), vec2(1.0, 0.0));
					break;
		//Segitiga siku-siku
		case 3	:	numberOfVertices = 3;
					vertices = new Node[3];
					vertices[0].setEverything(vec3(-0.5, -0.3, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(-0.5, 0.3, 0.0), vec2(0.0, 0.6));
					vertices[2].setEverything(vec3(0.6, -0.3, 0.0), vec2(0.8, 0.0));
					break;
		//Persegi panjang
		case 4	:	numberOfVertices = 4;
					vertices = new Node[4];
					vertices[0].setEverything(vec3(-0.6, -0.4, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(-0.6, 0.4, 0.0), vec2(0.0, 1.0));
					vertices[2].setEverything(vec3(0.6, 0.4, 0.0), vec2(1.0, 1.0));
					vertices[3].setEverything(vec3(0.6, -0.4, 0.0), vec2(1.0, 0.0));
					break;
		//Kotak
		case 5	:	numberOfVertices = 4;
					vertices = new Node[4];
					vertices[0].setEverything(vec3(-0.5, -0.5, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(-0.5, 0.5, 0.0), vec2(0.0, 1.0));
					vertices[2].setEverything(vec3(0.5, 0.5, 0.0), vec2(1.0, 1.0));
					vertices[3].setEverything(vec3(0.5, -0.5, 0.0), vec2(1.0, 0.0));
					break;
		//Trapesium
		case 6	:	numberOfVertices = 4;
					vertices = new Node[4];
					vertices[0].setEverything(vec3(-0.6, -0.4, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(-0.4, 0.4, 0.0), vec2(0.25, 1.0));
					vertices[2].setEverything(vec3(0.4, 0.4, 0.0), vec2(0.75, 1.0));
					vertices[3].setEverything(vec3(0.6, -0.4, 0.0), vec2(1.0, 0.0));
					break;
		//Layang-layang
		case 7	:	numberOfVertices = 4;
					vertices = new Node[4];
					vertices[0].setEverything(vec3(0.0, -0.75, 0.0), vec2(0.5, 0.0));
					vertices[1].setEverything(vec3(-0.5, 0.0, 0.0), vec2(0.0, 0.7));
					vertices[2].setEverything(vec3(0.0, 0.5, 0.0), vec2(0.5, 1.0));
					vertices[3].setEverything(vec3(0.5, 0.0, 0.0), vec2(1.0, 0.7));
					break;
		//Jajar genjang
		case 8	:	numberOfVertices = 4;
					vertices = new Node[4];
					vertices[0].setEverything(vec3(-0.6, -0.3, 0.0), vec2(0.0, 0.0));
					vertices[1].setEverything(vec3(-0.4, 0.3, 0.0), vec2(0.25, 0.75));
					vertices[2].setEverything(vec3(0.6, 0.3, 0.0), vec2(1.0, 0.75));
					vertices[3].setEverything(vec3(0.4, -0.3, 0.0), vec2(0.75, 0.0));
					break;
		//Poligon, segi berapapun
		case 9	:	cout << "Berapa sisi (sisi>4)?" << endl;
					do {
						cout << "Sisi : ";
						cin >> numberOfVertices;
						if (numberOfVertices<5) {
							cout << "Input salah, jumlah sisi harus lebih dari 4" << endl;
						}
					} while (numberOfVertices<5);
		
					vertices = buildCircleVerticesArray(0.0, 0.0, 0.0, 0.5, numberOfVertices);
					numberOfVertices += 2;
					break;
		//Lingkaran
		case 10	: 	numberOfVertices = 362;
					vertices = buildCircleVerticesArray(0.0, 0.0, 0.0, 0.5, 360);
					break;
		//Lingkaran
		default	: 	numberOfVertices = 362;
					vertices = buildCircleVerticesArray(0.5, 0.5, 0.0, 0.5, 360);
					break;
	}

	//Input tekstur
	string filename = textureChoices();

	//Ini pake SDL untuk windownya
	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL");

	//Untuk handle crash pas passing address of array di Mesh
	//Ternyata gak perlu tapi
	//glewExperimental = GL_TRUE;

	//Ciptain shape sesuai jenis vertice shape
	Shape shape(vertices, numberOfVertices, solid);
	//Pake arsir untuk warnain shape pake texture
	Shader arsir("./res/basicShader");
	//Tekstur yang dipake
	Texture tekstur(filename);

	//Kelas animateasi untuk animasi
	Animation animate;

	int factor = 100;

	GLfloat counter_x = 0.0f;
	GLfloat counter_y = 0.0f;
	GLfloat counter_rotate = 0.0f;
	GLfloat counter_scale = 0.0f;
	
	GLfloat counter_melingkar = 0.0f;
	GLfloat counter_bouncing = 0.0f;
	GLfloat counter_melayangjauh = 0.0f;
	GLfloat counter_melayanglayang = 0.0f;	
	
	while (!window.isClosed()) {
		//warna screen (r,g,b,a)
		if (filename== "./res/blue.jpg") {
			window.clear(0.1f, 0.2f, 0.3f, 1.0f);
		}
		else if (filename == "./res/brown.jpg") {
			window.clear(0.9f, 0.3f, 0.3f, 1.0f);
		}
		else if (filename == "./res/grey.png") {
			window.clear(0.75f, 0.75f, 0.75f, 1.0f);
		}

		switch (window.getType()) {

			case 9	:	//move up
						counter_y += 0.001f; 

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_Y(counter_y*factor);

						window.setType(0);
						break;

			case 10	:	//move down
						counter_y -= 0.001f;

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_Y(counter_y*factor);

						window.setType(0);
						break;

			case 11	:	//move left
						counter_x -= 0.001f; 

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_X(counter_x*factor);
						
						window.setType(0);
						break;

			case 12	:	//move right
						counter_x += 0.001f;

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_X(counter_x*factor);
						
						window.setType(0);
						break;

			case 1	:	//rotate left
						counter_rotate += 0.001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetRot_Z((counter_rotate)*factor / 2);

						window.setType(0);
						break;

			case 2	:	//rotate right
						counter_rotate -= 0.001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetRot_Z((counter_rotate)*factor / 2);

						window.setType(0);
						break;

			case 3	:	//scale up
						counter_scale += 0.001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetScale(vec3(cosf(counter_scale * 10), cosf(counter_scale * 10), cosf(counter_scale * 10)));

						window.setType(0);
						break;

			case 4	:	//scale down
						counter_scale -= 0.001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetScale(vec3(cosf(counter_scale * 10), cosf(counter_scale * 10), cosf(counter_scale * 10)));

						window.setType(0);
						break;

			case 5	:	//gerak melingkar
						counter_melingkar += 0.00001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_X(sinf(counter_melingkar*factor));
						animate.SetPos_Y(cosf(counter_melingkar*factor));

						break;

			case 6	:	//gerak melayang-layang
						counter_melayanglayang += 0.00001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
						animate.SetRot_Z(counter_melayanglayang * factor / 2);

						break;

			case 7	:	//gerak melayang jauh
						counter_melayangjauh += 0.00001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						animate.SetRot_Z((counter_rotate)*factor / 2);

						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_bouncing > 0) {
							animate.SetPos_X(cosf(counter_bouncing*factor / 4));
							animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
							animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));
						}

						animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
						animate.SetRot_Z(counter_melayangjauh * factor / 2);
						animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));

						break;

			case 8	:	//gerak memantul
						counter_bouncing += 0.00001f;

						animate.SetPos_X(counter_x*factor);
						animate.SetPos_Y(counter_y*factor);

						animate.SetRot_Z((counter_rotate)*factor / 2);
					
						if (counter_melingkar > 0) {
							animate.SetPos_X(sinf(counter_melingkar*factor));
							animate.SetPos_Y(cosf(counter_melingkar*factor));
						}

						if (counter_melayanglayang > 0) {
							animate.SetPos_X(cosf(counter_melayanglayang*factor / 2));
							animate.SetRot_Z(counter_melayanglayang * factor / 2);
						}

						if (counter_melayangjauh > 0) {
							animate.SetPos_X(sinf(counter_melayangjauh*factor / 2));
							animate.SetRot_Z(counter_melayangjauh * factor / 2);
							animate.SetScale(animate.GetScale()*cosf(counter_melayangjauh));
						}

						animate.SetPos_X(cosf(counter_bouncing*factor / 4));
						animate.SetRot_Z(counter_bouncing * 5 * factor / 4);
						animate.SetScale(vec3(cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4), cosf(counter_bouncing * 5 * factor / 4)));

						break;

			default	:	break;
		}

		arsir.Bind();
		tekstur.Bind();
		arsir.Update(animate);
		shape.Draw();
		window.updateBuffer();
	}

	return 0;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
	//x, y, z adalah koordinat titik pusatnya

	GLint numberOfVertices = numberOfSides + 2;

	GLfloat doublePi = 2.0f * (float)M_PI;

	GLfloat* circleVerticesX;
	GLfloat* circleVerticesY;
	GLfloat* circleVerticesZ;

	circleVerticesX = new GLfloat[numberOfVertices];
	circleVerticesY = new GLfloat[numberOfVertices];
	circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++) {
		circleVerticesX[i] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / numberOfSides));
		circleVerticesZ[i] = z;
	}

	GLfloat* allCircleVertices;
	//Gabung semua array x,y,z jadi satu array berurutan
	allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++) {
		allCircleVertices[i * 3 ]    = circleVerticesX[i];
		allCircleVertices[i * 3 + 1] = circleVerticesY[i];
		allCircleVertices[i * 3 + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete [] circleVerticesX;
	delete [] circleVerticesY;
	delete [] circleVerticesZ;
}

Node* buildCircleVerticesArray(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
	GLint numberOfVertices = numberOfSides + 2;

	GLfloat m = (GLfloat) M_PI;
	GLfloat two = (GLfloat) 2.0;
	GLfloat doublePi = two * m;

	Node* vertices;
	GLfloat* circleVerticesX;
	GLfloat* circleVerticesY;
	GLfloat* circleVerticesZ;

	vertices = new Node[numberOfVertices];
	circleVerticesX = new GLfloat[numberOfVertices];
	circleVerticesY = new GLfloat[numberOfVertices];
	circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;
	vertices[0].setEverything(vec3(circleVerticesX[0], circleVerticesY[0], circleVerticesZ[0]), vec2(0.0, 0.0));

	for (int i = 1; i < numberOfVertices; i++) {
		circleVerticesX[i] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / numberOfSides));
		circleVerticesZ[i] = z;
		vertices[i].setEverything(vec3(circleVerticesX[i], circleVerticesY[i], circleVerticesZ[i]), vec2(0.0, 0.0));
	}

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;

	return vertices;
}

int shapeChoices() {
	cout << "Pilih salah satu bangun di bawah ini!" << endl;
	cout << "1. Garis" << endl;
	cout << "2. Segitiga sama kaki" << endl;
	cout << "3. Segitiga siku2" << endl;
	cout << "4. Persegi panjang" << endl;
	cout << "5. Kotak" << endl;
	cout << "6. Trapesium" << endl;
	cout << "7. Layang-layang" << endl;
	cout << "8. Jajar genjang" << endl;
	cout << "9. Poligon (segi berapapun)" << endl;
	cout << "10. Lingkaran" << endl;
	
	int a;
	do {
		cout << "Pilihan angka: ";
		cin >> a;
		if ((a < 1) || (a > 10)) {
			cout << "Input salah, input angka antara 1 dan 10" << endl;
		}
	} while ((a < 1) || (a > 10));

	return a;
}

string textureChoices() {
	string filename = "";

	cout << "Pilih salah satu tekstur di bawah ini!" << endl;
	cout << "1. Biru" << endl;
	cout << "2. Coklat" << endl;
	cout << "3. Abu2" << endl;

	int a;
	do {
		cout << "Pilihan angka: ";
		cin >> a;
		if ((a < 1) || (a > 3)) {
			cout << "Input salah, input angka antara 1 dan 3" << endl;
		}
	} while ((a < 1) || (a > 3));

	if (a == 1) {
		filename = "./res/blue.jpg";
	}
	else if (a == 2) {
		filename = "./res/brown.jpg";
	}
	else if (a == 3) {
		filename = "./res/grey.png";
	}
	return filename;
}