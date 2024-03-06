#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Renderer.hh"
#include "ScreenSize.hh"
#include "Board.hh"
#include "Game.hh"
#include "Renderer.hh"

class Window
{
	public:
		explicit Window();
		~Window();
		void resize(SDL_Event e);
		Renderer* getRenderer() { return &renderer; }
	private:
		void setSizes() const;
		SDL_Window* window;
		Renderer renderer;
		int width;
		int height;
};


#endif
