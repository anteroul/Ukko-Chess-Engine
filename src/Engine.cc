#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	setOriginalPieces();

	rounds = 2;

	// clear existing stuff
	clearEngine();
	clearPlayer();

	// check if engine has moves
	getEngineMoves();

	if(!enginePairs.empty())
	{
		clearEngine();

		// perform minmax algorithm
		MinMax m = maxi(rounds);

		// set all squares back to normal
		setOriginalPieces();

		/*
		 *	We want to pass pointers from actual squares to Move.
		 *	Hence this, since Sqr::squareHelper returns pointer to correct square.
		 *	Both bestMove->first and second are just copies, either from oldPieces or LegalMoves.
		 *
		 */
		Move::execute(Sqr::squareHelper(m._bestMove->first.x, m._bestMove->first.y), 
				Sqr::squareHelper(m._bestMove->second.x, m._bestMove->second.y), true);

		return true;
	}
	else
	{
		if(Global::engineInCheck)
			Global::state = VICTORY;
		else
			Global::state = DRAW;
		return false;
	}
}

// returns the best move for the engine
MinMax Engine::engineBest()
{
	getEngineMoves();

	std::pair<Square, Square>* m = nullptr; 

	double balance = oldEvaluate();

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		// evaluate move
		double a = oldEvaluate() + 0.01;

		if(a > balance)
		{
			m = &enginePairs[i];
			balance = a;
		}
	}

	return MinMax(balance, m);
}

MinMax Engine::playerBest()
{
	getPlayerMoves();

	std::pair<Square, Square>* m = nullptr;

	double balance = oldEvaluate();

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		double a = oldEvaluate() + 0.01;

		if(a > balance)
		{
			m = &playerPairs[i];
			balance = a;
		}
	}

	return MinMax(balance, m);
}

double Engine::oldEvaluate()
{
	// king multiplier
	
	Piece* engineKing = nullptr;
	Piece* playerKing = nullptr;
	
	// FOR ENGINE
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(Sqr::getSquare(i, j).piece.user == ENGINE)
				if(Sqr::getSquare(i, j).piece.type == KING)
					engineKing = &Sqr::getSquare(i, j).piece;
					
	// POSITION
	// OWN PIECES NEAR ++
	// ENEMY PIECES NEAR --
	
	
	
	
	// center multiplier
	// line multiplier

	getMaterialBalance();
	double calc = engineMaterial - playerMaterial;
	
	// this is just an example conversion
	double eval = calc / 20;
	
	// maybe we have some use for this later dunno
	Global::evaluation = eval;
	return eval;
}

void Engine::setOriginalPieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			oldPieces[i][j] = Sqr::getSquare(i, j);
}

void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

MinMax Engine::maxi(int depth)
{
	if(depth == 0)
		return engineBest();

	getEngineMoves();

	int score = 0;
	int max = INT_MIN;
	std::pair<Square, Square>* m = nullptr;

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		setOriginalPieces();

		// make fake move
		makeFakeMove(&enginePairs[i]);

		// call to min
		MinMax move = mini(depth - 1);

		score = move._evaluation;

		if(score > max)
		{
			max = score;
			m = move._bestMove;
		}
	}
	
	return MinMax(max, m);
}

MinMax Engine::mini(int depth)
{
	if(depth == 0) 
		return playerBest();

	getPlayerMoves();

	int score = 0;
	int min = INT_MAX;
	std::pair<Square, Square>* m = nullptr;

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		makeFakeMove(&playerPairs[i]);
		
		MinMax move = maxi(depth - 1);
		score = move._evaluation;

		if(score < min)
		{
			min = score;
			m = move._bestMove;
		}
	}
	
	return MinMax(min, m);
}

double Engine::materialValue(bool player)
{
	double n = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(player && Sqr::getSquare(i, j).piece.user == PLAYER)
				n += getValue(Sqr::getSquare(i, j));

			if((!player) && Sqr::getSquare(i, j).piece.user == ENGINE)
				n += getValue(Sqr::getSquare(i, j));
		}
	}
	
	return n;
}

double Engine::getValue(Square square)
{
	double n = 0;
	switch(square.piece.type)
	{
		case KING: n += 1000; break; // might not be final
		case NONE: break;
		case ROOK: n += 5; break;
		case PAWN: n += 1; break;
		case QUEEN: n += 9; break;
		case KNIGHT: n += 3; break;
		case BISHOP: n += 3.25; break;
	}
	return n;
}

void Engine::makeFakeMove(std::pair<Square, Square>* move)
{
	Move::execute(&move->first, &oldPieces[move->second.x][move->second.y], false);
}

void Engine::getEnginePieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(oldPieces[i][j].piece.user == ENGINE)
				enginePieces.push_back(oldPieces[i][j]);
}

void Engine::getPlayerPieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(oldPieces[i][j].piece.user == PLAYER)
				playerPieces.push_back(oldPieces[i][j]);
}

void Engine::getEngineMoves()
{
	// get all pieces first
	if(!enginePieces.empty())
		enginePieces.clear();
	
	if(!enginePairs.empty())
		enginePairs.clear();

	getEnginePieces();

	for(auto& i : enginePieces)
	{
		// get legal moves for the piece
		std::vector<Square> moves = LegalMove::getLegal(i.piece);

		for(auto& j : moves)
			enginePairs.push_back(std::make_pair(i, j));
	}
}

void Engine::getPlayerMoves()
{
	if(!enginePieces.empty())
		enginePieces.clear();

	if(!enginePairs.empty())
		enginePairs.clear();

	getPlayerPieces();

	for(auto& i : playerPieces)
	{
		std::vector<Square> moves = LegalMove::getLegal(i.piece);
		for(auto& j : moves)
			playerPairs.push_back(std::make_pair(i, j));
	}
}

void Engine::clearEngine()
{
	enginePieces.clear();
	enginePairs.clear();
}

void Engine::clearPlayer()
{
	playerPieces.clear();
	playerPairs.clear();
}



