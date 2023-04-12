#ifndef PIECEFACTORY_HH
#define PIECEFACTORY_HH

#include <SDL2/SDL.h>
#include <string>
#include "Texture.hh"
#include "Board.hh"
#include "Global.hh"

class PieceFactory {
public:
    PieceFactory();

    ~PieceFactory();

    // get texture
    SDL_Texture *getPiece(int n);

private:

    // the textures
    SDL_Texture *p[16]{};

    std::string c[16] = {
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
            "Assets/wr.png",
            "Assets/bishop_btn.png",
            "Assets/knight_btn.png",
            "Assets/queen_btn.png",
            "Assets/rook_btn.png"
    };
};

#endif

