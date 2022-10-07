#ifndef UKKOSHAKKI_BUTTON_HH
#define UKKOSHAKKI_BUTTON_HH

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Piece.hh"

struct Button {
	Type value;
	Sint16 x, y;
	Uint16 w, h;
	SDL_Texture& icon;
};

#endif //UKKOSHAKKI_BUTTON_HH
