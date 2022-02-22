#ifndef PIECERENDERER_HH
#define PIECERENDERER_HH

#include <iostream>
#include "Renderer.hh"
#include "PieceFactory.hh"
#include "Piece.hh"
#include "SquareManager.hh"
#include "Global.hh"

namespace PieceRenderer
{
	void init(PieceFactory* factory);
	void renderInPosition(Piece piece);
}

#endif

