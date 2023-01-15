#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include <SDL2/SDL.h>
#include "Square.hh"
#include "SquareManager.hh"
#include "ScreenSize.hh"
#include "Renderer.hh"
#include "Button.hh"
#include <vector>

class GUI
{
public:
	static bool onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square);
	static Square *onSelect(SDL_Point &mousePos);
	static void displayPromotionTable(const std::vector<Button*> &btn);
};


#endif //UKKOSHAKKI_GUI_HH
