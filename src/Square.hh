#ifndef SQUARE_HH
#define SQUARE_HH

#include "Piece.hh"
#include <SDL2/SDL.h>

typedef struct Square
{
	//Square() { Square::piece = new Piece; };
	//~Square() { delete Square::piece; };
	SDL_Rect rect;
	Piece* piece = nullptr;
	int x, y;

} Square;

#endif

