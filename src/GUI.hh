#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include <SDL2/SDL.h>
#include "Square.hh"
#include "SquareManager.hh"
#include "ScreenSize.hh"
#include "Text.hh"
#include "Texture.hh"
#include "Window.hh"
#include "Global.hh"
#include "Game.hh"
#include <vector>
#include <functional>

class GUI : protected Game
{
public:
	GUI() = default;
	static bool onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square);
	static Square *onSelect(SDL_Point &mousePos);
};

class Cursor : public GUI
{
public:
	void updateCursor()
	{
		// when mouse is moved
		if (e.type == SDL_MOUSEMOTION)
		{
			// Get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
		}
	}
};

class PromotionTable : public GUI
{
public:
	PromotionTable()
	{
		promotionTableTooltips = Texture::load("../Assets/Other/tooltips.png", *renderer);
	}

	~PromotionTable()
	{
		Global::inPromotion = false;
		SDL_DestroyTexture(promotionTableTooltips);
		delete[] &tooltips;
	}

	void render(Renderer& ren)
	{

		tableCanvas = {Screen::getWidth() / 8, Screen::getHeight() / 5, (Screen::getWidth() / 4 * 3),
		               Screen::getHeight() / 2};
		ren.setColor(128, 128, 128);
		ren.fillRect(tableCanvas);

		// render tooltips
		/*
		for (auto & i : tooltips)
			i.render();
		*/
		// band-aid solution:

		SDL_RenderCopy(ren.renderer, promotionTableTooltips, nullptr, &tableCanvas);
	}
private:
	// displays during pawn promotion
	SDL_Rect tableCanvas = {Screen::getWidth() / 8, Screen::getHeight() / 5, (Screen::getWidth() / 4 * 3),
	               Screen::getHeight() / 2};

	SDL_Texture *promotionTableTooltips;
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
