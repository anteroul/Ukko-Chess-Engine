#ifndef BOARD_HH
#define BOARD_HH

#include <SDL2/SDL.h>
#include "ScreenSize.hh"
#include "Window.hh"
#include "SquareManager.hh"

class Board
{
public:
	Board(Window &win);
	void render();
	void makeBoard() const;
	void makeRects();
private:
	Renderer* renderer = nullptr;
	// source and destination for texture
	SDL_Rect srcrect{};
	SDL_Rect dstrect{};
};

#endif
