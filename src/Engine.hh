#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include "SquareManager.hh"
#include "MinMax.hh"
#include <vector>
#include <iostream>
#include <map>
#include <climits>

class Engine
{
public:
	Engine();
	~Engine();
	static void executeMove(Square* source, Square& target);
	bool moveSetup();
private:
	std::vector<Square> playerMoves;
	std::vector<Square> legalMoves;
	std::vector<Piece> playerPieces;
};

#endif