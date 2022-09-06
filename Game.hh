#ifndef GAME_HH
#define GAME_HH

#include "Board.hh"
#include "GUI.hh"
#include "LegalMoves.hh"
#include "Piece.hh"
#include "PieceFactory.hh"
#include "PieceRenderer.hh"
#include "Settings.hh"
#include "Square.hh"
#include "SquareManager.hh"
#include "Window.hh"
#include "Pieces.hh"
#include "Move.hh"
#include "Global.hh"
#include "Text.hh"
#include "GameManager.hh"
#include <chrono>
#include <thread>

class Game
{
public:
	Game();
	~Game();
	void updateGame();
	bool ApplicationShouldClose = false;
private:
	bool moveSetup();
	void playerPlayMove();
	void enginePlayMove();
	void render();
	void update();
	void eventHandler();
	void resetGame();
	void updateConsoleText(const std::string &text);
	void executePlayerMove(Square &sq);

	std::vector<Square> playerMoves;
	std::vector<Square> legalMoves;
	std::vector<Piece> playerPieces;

	// console stuff
	std::vector<Text *> console;
	int consoleIndex = 0;
	bool isPieceSelected = false;
	void updateConsole();

	Board *board = nullptr;
	PieceFactory *pieces = nullptr;
	Window *window = nullptr;
	SDL_Event e{};
	SDL_Point mousePos = {0, 0};
	Square *selectedSquare = nullptr;
	Square *originalSquare = nullptr;
};

#endif
