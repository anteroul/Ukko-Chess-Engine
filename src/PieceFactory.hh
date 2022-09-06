#ifndef PIECEFACTORY_HH
#define PIECEFACTORY_HH

#include <SDL2/SDL.h>
#include <string>
#include "Texture.hh"
#include "Board.hh"
#include "Global.hh"

class PieceFactory
{
	public:
		PieceFactory();
		~PieceFactory();

		// get texture
		SDL_Texture* getPiece(int n);
		SDL_Texture* getButton(int n);

	private:
		
		// the textures
		SDL_Texture* p[12]{};
		SDL_Texture* b[8]{};

		std::string c[12] = 
		{
			"Assets/bb.png",
			"Assets/bh.png",
			"Assets/bk.png",
			"Assets/bp.png",
			"Assets/bq.png",
			"Assets/br.png",
			"Assets/wb.png",
			"Assets/wh.png",
			"Assets/wk.png",
			"Assets/wp.png",
			"Assets/wq.png",
			"Assets/wr.png"
		};

		// the button icons
		std::string btn_src[8] =
		{
			"Assets/bb_btn.png",
			"Assets/bh_btn.png",
			"Assets/bq_btn.png",
			"Assets/br_btn.png",
			"Assets/wb_btn.png",
			"Assets/wh_btn.png",
			"Assets/wq_btn.png",
			"Assets/wr_btn.png"
		};
};

#endif

