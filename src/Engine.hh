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
    bool PlayMove();
private:
    // get all pieces
    void getEnginePieces();
    void getPlayerPieces();
    std::vector<Square> enginePieces;
    std::vector<Square> playerPieces;

    // get all possible moves
    void getEngineMoves();
    void getPlayerMoves();
	std::vector<std::pair<Square, Square>> enginePairs;
    std::vector<std::pair<Square, Square>> playerPairs;

    // get the best possible move
    MinMax engineBest();
    MinMax playerBest();
    
	// evaluation
    void getMaterialBalance();
    int evaluate();
	double oldEvaluate();
    double materialValue(bool player);
    static double getValue(Square square);
	double engineMaterial;
    double playerMaterial;

    // minmax
    MinMax mini(int depth);
    MinMax maxi(int depth);

	// fake move stuff
    void makeFakeMove(std::pair<Square, Square>* move);
	void setOriginalSquares();
	void updateSquares();

	Square currentSquares[8][8];
	Square originalSquares[8][8];

	// helper functions
	void clearEngine();
    void clearPlayer();

	int rounds;
	
};

#endif
