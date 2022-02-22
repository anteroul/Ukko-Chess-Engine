#ifndef SQUAREMANAGER_HH
#define SQUAREMANAGER_HH

#include "Square.hh"
#include "Piece.hh"

namespace Sqr
{
	void makeSquares();
	Square& getSquare(int x, int y);
	Square* squareHelper(int x, int y);
	Square squareCopy(int x, int y);

	void setPiece(Piece* p);
	Piece* getPiece(int x, int y);
}

#endif
