#include "PieceRenderer.hh"
#include "Renderer.hh"
#include "SquareManager.hh"

PieceFactory *_factory = nullptr;

void PieceRenderer::init(PieceFactory *factory)
{
	_factory = factory;
}

void PieceRenderer::renderInPosition(Piece piece, Renderer& ren)
{
	int n = -1;

	// corresponding value from PieceFactory
	switch (piece.type)
	{
		case KING:
			n = (piece.color == BLACK) ? 2 : 8;
			break;
		case PAWN:
			n = (piece.color == BLACK) ? 3 : 9;
			break;
		case ROOK:
			n = (piece.color == BLACK) ? 5 : 11;
			break;
		case KNIGHT:
			n = (piece.color == BLACK) ? 1 : 7;
			break;
		case QUEEN:
			n = (piece.color == BLACK) ? 4 : 10;
			break;
		case BISHOP:
			n = (piece.color == BLACK) ? 0 : 6;
			break;
		case NONE:
			n = -1;
			break;
	}

	// render the piece
	if (n != -1)
		SDL_RenderCopy(ren.renderer, _factory->getPiece(n), nullptr, &Sqr::getSquare(piece.x, piece.y).rect);
}


