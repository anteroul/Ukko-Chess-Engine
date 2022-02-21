#include "Global.hh"

currentGameState Global::state = GAME_ON;

void Global::ghost(Piece* p)
{
	p->type = NONE;
	p->color = UNDEFINED;
	p->user = GHOST;
}

void Global::ghostXY(int x, int y)
{
	Piece* p = Sqr::squareHelper(x, y)->piece;
	p->type = NONE;
	p->color = UNDEFINED;
	p->user = GHOST;
}

bool Global::playerTurn = true;

Square* Global::en_passant = nullptr;

double Global::evaluation = 0;


bool Global::playerKingMoved = false;
bool Global::engineKingMoved = false;
bool Global::playerQsideRookMoved = false;
bool Global::playerKsideRookMoved = false;
bool Global::engineQsideRookMoved = false;
bool Global::engineKsideRookMoved = false;

bool Global::playerCanCastleK = true;
bool Global::playerCanCastleQ = true;
bool Global::engineCanCastleK = true;
bool Global::engineCanCastleQ = true;

bool Global::playerInCheck = false;
bool Global::engineInCheck = false;


