#ifndef UKKOSHAKKI_BUTTON_HH
#define UKKOSHAKKI_BUTTON_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Piece.hh"
#include "PieceFactory.hh"
#include "Global.hh"

class Button
{
public:
	Button(PieceFactory* factory, Type value);
	SDL_Texture* getButtonTexture();
	SDL_Rect getRect();
private:
	Sint16 x, y;
	Uint16 w, h;
	SDL_Texture* icon;
};

#endif //UKKOSHAKKI_BUTTON_HH
