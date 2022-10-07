#ifndef PIECE_HH
#define PIECE_HH

enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE } Type;
enum { BLACK, WHITE, UNDEFINED } Color;
enum { PLAYER, ENGINE, GHOST } User;

struct Piece
{
	Type type;
	Color color;
	int x, y;
	User user;
};


#endif

