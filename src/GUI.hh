#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include <SDL2/SDL.h>
#include "Square.hh"
#include "SquareManager.hh"
#include "ScreenSize.hh"
#include "Text.hh"
#include "Texture.hh"
#include "Global.hh"
#include <vector>

class GUI
{
public:
	static bool onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square);
	static Square *onSelect(SDL_Point &mousePos);
};

struct PromotionTable : public GUI {
    PromotionTable()
    {
        // displays during pawn promotion
		canvas = {Screen::getWidth() / 8, Screen::getHeight() / 5, (Screen::getWidth() / 4 * 3), Screen::getHeight() / 2};
		promotionTableTooltips = Texture::load("../Assets/Other/tooltips.png");
    }

    ~PromotionTable()
    {
		Global::inPromotion = false;
		SDL_DestroyTexture(promotionTableTooltips);
    }

    SDL_Rect canvas{};
    SDL_Texture* promotionTableTooltips;
    /*
     * TODO: Promotion GUI buttons
     SDL_Texture* promotionButtons[4] = {

     };
    */
    Text tooltips[4] = {
			Text("NUM1: QUEEN", 0.4f, 0.4f),
			Text("NUM2: ROOK", 0.4f, 0.5f),
			Text("NUM3: KNIGHT", 0.4f, 0.6f),
			Text("NUM4: BISHOP", 0.4f, 0.7f),
    };
};



#endif //UKKOSHAKKI_GUI_HH
