#include "Pieces.hh"

namespace Pieces
{
	// the pieces
	static Piece p[64];

	Piece& get(int n) { return p[n]; }

	Piece* getModify(int n) { return &p[n]; }

	void set(Piece piece, int x, int y)
	{
		for(int i = 0; i < 64; i++)
		{
			if(get(i).x == x && get(i).y == y)
			{
				Piece* temp = &p[i];
                temp->color = piece.color;
                temp->type = piece.type;
                temp->user = piece.user;
			}
		}
	}

	Piece& getReal(Piece* piece)
	{
		for(int i = 0; i < 64; i++)
			if(p[i].x == piece->x && p[i].y == piece->y
			&& p[i].user == piece->user && p[i].type == piece->type)
				return p[i];

		// TODO fix this, although this should never happen
		
		return p[31];
	}

	void init()
	{
		// 0-7 		ENGINE PAWNS
		// 8-15 	ENGINE PIECES
		// 16-23 	PLAYER PAWNS
		// 24-31 	PLAYER PIECES
	
		Color engineColor = BLACK;
		Color PlayerColor = WHITE;
	
		// engine pawns
		for(int i = 0; i < 8; i++)
		{
			p[i] = { PAWN, engineColor, i, 1, ENGINE };
			Sqr::setPiece(&p[i]);
		}

		// player pawns
		for(int i = 16; i < 24; i++)
		{
			p[i] = { PAWN, PlayerColor, (i - 16), 6, PLAYER };
			Sqr::setPiece(&p[i]);
		}

		// engine pieces
		p[8] = { ROOK, engineColor, 0, 0, ENGINE };
		p[9] = { ROOK, engineColor, 7, 0, ENGINE };
		p[10] = { KNIGHT, engineColor, 1, 0, ENGINE };
		p[11] = { KNIGHT, engineColor, 6, 0, ENGINE };
		p[12] = { BISHOP, engineColor, 2, 0, ENGINE };
		p[13] = { BISHOP, engineColor, 5, 0, ENGINE };
		p[14] = { QUEEN, engineColor, 3, 0, ENGINE };
		p[15] = { KING, engineColor, 4, 0, ENGINE };

		// player pieces
		p[24] = { ROOK, PlayerColor, 0, 7, PLAYER };
		p[25] = { ROOK, PlayerColor, 7, 7, PLAYER };
		p[26] = { KNIGHT, PlayerColor, 1, 7, PLAYER };
		p[27] = { KNIGHT, PlayerColor, 6, 7, PLAYER };
		p[28] = { BISHOP, PlayerColor, 2, 7, PLAYER };
		p[29] = { BISHOP, PlayerColor, 5, 7, PLAYER };
		p[30] = { QUEEN, PlayerColor, 3, 7, PLAYER };
		p[31] = { KING, PlayerColor, 4, 7, PLAYER };


		for(int i = 8; i < 16; i++)
		{
			Sqr::setPiece(&p[i]);
		}

		for(int i = 25; i < 32; i++)
		{
			Sqr::setPiece(&p[i]);
		}

		int a = 2, b = 0;
		for(int i = 32; i < 64; i++)
		{
			(a < 6) ? a++ : a = 2;
			(b < 8) ? b++ : b = 0;
			p[i] = { NONE, UNDEFINED, a, b, GHOST };
			Sqr::setPiece(&p[i]);
		}
	}
}
