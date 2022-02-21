#ifndef GLOBAL_HH
#define GLOBAL_HH

#ifdef __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#ifdef __LINUX__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#ifdef __WIN32__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "Piece.hh"
#include "Square.hh"
#include "SquareManager.hh"


#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

typedef enum { GAME_ON, VICTORY, DEFEAT, DRAW, END } currentGameState;

class Global
{
	public:
		// 1 ENGINE WIN -- -1 ENGINE LOSE
		static double evaluation;

		static bool playerTurn;
		static currentGameState state;
		static Square en_passant;

		// castling
		static bool playerKingMoved;
		static bool playerQsideRookMoved;
		static bool playerKsideRookMoved;

		static bool engineKingMoved;
		static bool engineQsideRookMoved;
		static bool engineKsideRookMoved;

		static bool playerCanCastleK;
		static bool playerCanCastleQ;
		static bool engineCanCastleK;
		static bool engineCanCastleQ;

		// check
		static bool playerInCheck;
		static bool engineInCheck;

		static void ghost(Piece* piece);
		static void ghostXY(int x, int y);
};

#endif
