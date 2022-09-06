#include "Game.hh"

Game::Game()
{
	// create new window and renderer
	window = new Window;

	// make board
	board = new Board;

	// create pieces
	pieces = new PieceFactory;

	// initialize helping namespace
	PieceRenderer::init(pieces);

	// initialize pieces in their correct places
	Pieces::init();

	// white starts game
	Settings::PlayerColor == WHITE ? Global::playerTurn = true : Global::playerTurn = false;
}

Game::~Game()
{
	delete pieces;
	delete board;
	delete window;
}

void Game::updateGame()
{
	eventHandler();
	update();
	render();
}

void Game::eventHandler()
{
	while (SDL_PollEvent(&e))
	{
		// resize window
		window->resize(e);

		// close application
		if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
			ApplicationShouldClose = true;

		// when mouse is moved
		if (e.type == SDL_MOUSEMOTION)
		{
			// Get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
		}

		// when mouse is clicked
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			// get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			selectedSquare = GUI::onSelect(mousePos);

			// render possible moves
			if (Global::playerTurn)
			{
				if (selectedSquare->piece.type != NONE && selectedSquare->piece.user == PLAYER)
				{
					originalSquare = selectedSquare;
					legalMoves = LegalMove::getLegal(originalSquare->piece);
					isPieceSelected = true;
				}
			}
			else
			{
				if (selectedSquare->piece.type != NONE && selectedSquare->piece.user == ENGINE)
				{
					originalSquare = selectedSquare;
					legalMoves = LegalMove::getLegal(originalSquare->piece);
					isPieceSelected = true;
				}
			}
		}

		// pawn promotion
		if (Global::inPromotion)
		{
			/*
			Piece* pieceToPromote;
			// loop players pieces to find the correct one
			for (int i = 0; i < 32; i++)
			{
				if (Pieces::get(i).type == PAWN && (Pieces::get(i).y == 0 || Pieces::get(i).y == 7))
				{
					pieceToPromote = Pieces::getModify(i);
					break;
				}
			}
			std::cout << "CHOOSE PIECE:\n";
			showPieces
			char choice;
			std::cin >> choice;

			switch (choice)
			{
				case 'Q':
					pieceToPromote->type = QUEEN;
					Global::inPromotion = false;
					break;
				case 'R':
					pieceToPromote->type = ROOK;
					Global::inPromotion = false;
					break;
				case 'B':
					pieceToPromote->type = BISHOP;
					Global::inPromotion = false;
					break;
				case 'K':
					pieceToPromote->type = KNIGHT;
					Global::inPromotion = false;
					break;
				default:
					std::cout << "INCORRECT OPTION\nCHOOSE AGAIN!\n";
					showPieces
					break;
			}
			*/
		}

		// if game is over press 'R' to reset and play again :)
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
			resetGame();
	}
}

// update turns
void Game::update()
{
	if (Global::state == GAME_ON)
		Global::playerTurn ? playerPlayMove() : enginePlayMove();
}

void Game::render()
{
	// make gray background
	Renderer::setColor(64, 64, 64);
	Renderer::clear();

	// render console
	for (auto & i : console)
		if (i)
			i->render();

	// render board
	board->render();

	if (selectedSquare)
	{
		// color selected square
		Renderer::setColor(0, 0, 255);
		Renderer::fillRect(selectedSquare->rect);
	}

	for(auto& legalMove : legalMoves)
	{
		if(selectedSquare && isPieceSelected)
		{
			// color legal moves
			Renderer::setColor(255, 0, 0);
			Renderer::fillRect(legalMove.rect);
		}
	}

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			// color the square where the mouse is
			if (GUI::onMouseRollOver(mousePos, Sqr::getSquare(i, j).rect))
			{
				Renderer::setColor(0, 255, 0);
				Renderer::fillRect(Sqr::getSquare(i, j).rect);
			}
		}
	}

	// render pieces
	for (int i = 0; i < 32; i++)
		PieceRenderer::renderInPosition(Pieces::get(i));

	if (Global::inPromotion)
		GUI::displayPromotionTable();

	// main rendering
	Renderer::render();
}

bool Game::moveSetup()
{
	playerPieces.clear();
	playerMoves.clear();

	if (Global::playerTurn)
	{
		// "raw pieces"
		for (int i = 16; i < 32; i++)
			playerPieces.push_back(Pieces::get(i));

		// loop all pieces
		for (auto &i: playerPieces)
		{
			// filter pieces
			if (i.type != NONE && i.user == PLAYER)
			{
				// get all legal moves
				std::vector<Square> temp = LegalMove::getLegal(i);

				for (auto &j: temp)
					playerMoves.push_back(j);
			}
		}
	}
	else
	{
		// "raw pieces"
		for (int i = 0; i < 16; i++)
			playerPieces.push_back(Pieces::get(i));

		// loop all pieces
		for (auto &i: playerPieces)
		{
			// filter pieces
			if (i.type != NONE && i.user == ENGINE)
			{
				// get all legal moves
				std::vector<Square> temp = LegalMove::getLegal(i);

				for (auto &j: temp)
					playerMoves.push_back(j);
			}
		}
	}

	return !playerMoves.empty();
}

void Game::playerPlayMove()
{
	GameManager::update();

	if(!moveSetup())
	{
		if(Global::playerInCheck)
			Global::state = DEFEAT;
		else
			Global::state = DRAW;
	}
	else
	{
		// if selected new square
		if (selectedSquare != originalSquare && isPieceSelected)
		{
			// loop legal moves for the selected piece
			for (auto& i : legalMoves)
            {
                if (selectedSquare->x == i.x && selectedSquare->y == i.y)
                    executePlayerMove(i);
                else
                    isPieceSelected = false;
            }
		}
	}
}

// Engine's move:
void Game::enginePlayMove()
{
	GameManager::update();

	if(!moveSetup())
	{
		if(Global::engineInCheck)
			Global::state = VICTORY;
		else
			Global::state = DRAW;
	}
	else
	{
		// if selected new square
		if (selectedSquare != originalSquare && isPieceSelected)
		{
			// loop legal moves for the selected piece
			for (auto& i : legalMoves)
			{
				if (selectedSquare->x == i.x && selectedSquare->y == i.y)
					executePlayerMove(i);
				else
					isPieceSelected = false;
			}
		}
	}
}

void Game::executePlayerMove(Square& sq)
{
	// loop players pieces to find the correct one
	for (int i = 0; i < 32; i++)
	{
		// filter moves
		if ((Global::playerTurn && Pieces::get(i).user == PLAYER && Pieces::get(i).type != NONE)
			|| (!Global::playerTurn && Pieces::get(i).user == ENGINE && Pieces::get(i).type != NONE))
		{
			if (originalSquare == &Sqr::getSquare(Pieces::get(i).x, Pieces::get(i).y))
			{
				// pawn promotion
				if ((Pieces::get(i).type == PAWN && Pieces::get(i).user == PLAYER && (sq.y == 0 || sq.y == 7) && Global::playerTurn)
				|| (Pieces::get(i).type == PAWN && Pieces::get(i).user == ENGINE && (sq.y == 0 || sq.y == 7) && !Global::playerTurn))
					Global::inPromotion = true;

				// make the move
				Move::execute(&Pieces::get(i), sq);
				legalMoves.clear();
				isPieceSelected = false;
				updateConsole();

				if (Global::playerTurn)
					Global::playerTurn = false;
				else
					Global::playerTurn = true;
			}
		}
	}
}

// update console output
void Game::updateConsole()
{
	switch (Global::state)
	{
		case GAME_ON:
			updateConsoleText(Move::getName());
			break;
		case VICTORY:
			updateConsoleText("Checkmate! You won!");
			Global::state = END;
			break;
		case DEFEAT:
			updateConsoleText("Checkmate! You lost.");
			Global::state = END;
			break;
		case DRAW:
			updateConsoleText("Draw!");
			Global::state = END;
			break;
		default:
			break;
	}

	if (Global::state == END)
		updateConsoleText("Hit 'R' to play again.");
}

void Game::updateConsoleText(const std::string& text)
{
	console.push_back(new Text(text, Global::playerTurn));
	consoleIndex++;

	for (auto &i: console)
		i->position.y -= 18;
}

// reset game variables
void Game::resetGame()
{
	// pieces to their correct places
	Pieces::init();

	// gameplay settings to normal
	Global::playerKingMoved = false;
	Global::engineKingMoved = false;
	Global::playerQsideRookMoved = false;
	Global::playerKsideRookMoved = false;
	Global::engineQsideRookMoved = false;
	Global::engineKsideRookMoved = false;
	Global::playerCanCastleK = true;
	Global::playerCanCastleQ = true;
	Global::engineCanCastleK = true;
	Global::engineCanCastleQ = true;
	Global::playerInCheck = false;
	Global::engineInCheck = false;

	// set game to ON
	Global::state = GAME_ON;

	// white starts game
	Settings::PlayerColor == WHITE ? Global::playerTurn = true : Global::playerTurn = false;

	// unselect square
	originalSquare = nullptr;
	selectedSquare = nullptr;

	// clear console
	console.clear();
}

