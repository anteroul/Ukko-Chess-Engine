#ifndef UKKOSHAKKI_BUTTON_HH
#define UKKOSHAKKI_BUTTON_HH

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Piece.hh"

typedef struct Button {
	Type value;
	int x, y, w, h;
	SDL_Texture& icon;
} Button;

#endif //UKKOSHAKKI_BUTTON_HH
