#ifndef SQUARE_HH
#define SQUARE_HH

#include "Piece.hh"
#include "Global.hh"

typedef struct Square
{
	SDL_Rect rect;
	Piece* piece = nullptr;
	int x, y;

} Square;

#endif

