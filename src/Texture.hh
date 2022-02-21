#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <iostream>
#include <string>
#include "Renderer.hh"
#include "ScreenSize.hh"

namespace Texture
{
	SDL_Texture* load(std::string path);
}

#endif