#ifndef WINDOW_H
#define	WINDOW_H
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
using namespace std;

#pragma once
class Window
{
	//Intinya kelas ini pake SDL untuk set up window
public:
	Window(int, int, const string&);
	virtual ~Window();

	void updateBuffer();
	void clear(float, float, float, float);
	bool isClosed();

	//Setter getter animation type
	void setType(const int&);
	int getType();

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	int animationType;
	
	bool closed;
};


#endif //WINDOW_H


