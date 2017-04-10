#include "Window.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Window::Window(int width, int height, const string& s) {

	//Untuk handle crash pas passing address of array di Mesh
	//Ternyata gak perlu tapi
	//glewExperimental = GL_TRUE;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //second buffer added, but not displayed, untuk nanti refresh buffer

	window = SDL_CreateWindow(s.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		cerr << "Glew not OK!" << endl;
	}

	closed = false;

	animationType = 0;
}

Window::~Window() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::updateBuffer() {
	SDL_GL_SwapWindow(window);

	SDL_Event evt;

	while (SDL_PollEvent(&evt)) {
		if (evt.type==SDL_QUIT) {
			closed = true;
		} else if (evt.type == SDL_KEYDOWN) {
			
			switch (evt.key.keysym.sym) {

				case SDLK_1:
					animationType = 1;
					break;

				case SDLK_2:
					animationType = 2;
					break;

				case SDLK_3:
					animationType = 3;
					break;

				case SDLK_4:
					animationType = 4;
					break;

				case SDLK_5:
					animationType = 5;
					break;

				case SDLK_6:
					animationType = 6;
					break;
				
				case SDLK_7:
					animationType = 7;
					break;

				case SDLK_8:
					animationType = 8;
					break;

				case SDLK_UP:
					animationType = 9;
					break;

				case SDLK_DOWN:
					animationType = 10;
					break;

				case SDLK_LEFT:
					animationType = 11;
					break;

				case SDLK_RIGHT:
					animationType = 12;
					break;

				default:
					break;
			}
		}
	}
}

void Window::clear(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::isClosed() {
	return closed;
}

void Window::setType(const int & t) {
	animationType = t;
}

int Window::getType() {
	return animationType;
}


