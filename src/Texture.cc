#include "Texture.hh"

namespace Texture
{
	SDL_Texture* load(std::string path)
	{
		Renderer::clear();
		std::string retryPath;

		// backup surface if something goes wrong
		SDL_Surface *newSurface = nullptr;

		// the actual texture
		SDL_Texture *texture = nullptr;

		// load image
		SDL_Surface *loadedSurface = IMG_Load(path.c_str());

		if (!loadedSurface)
		{
			SDL_FreeSurface(loadedSurface);
			retryPath = "../" + path;
		}

		newSurface = IMG_Load(retryPath.c_str());

		if (!newSurface)
		{
			std::cout << "Unable to load image: " << path.c_str() << " " << IMG_GetError() << "\n";
			std::cout << "Unable to load image: " << retryPath.c_str() << " " << IMG_GetError() << "\n";
			SDL_FreeSurface(newSurface);
			return nullptr;
		}

		if (loadedSurface)
		{
			// color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			// create texture from pixels
			texture = SDL_CreateTextureFromSurface(Renderer::get(), loadedSurface);

			if (!texture)
				std::cout << "Unable to create texture: " << path.c_str() << " " << SDL_GetError() << "\n";

			// get rid of loaded surface
			SDL_FreeSurface(loadedSurface);
		}
		if (!texture && newSurface)
		{
			// color key image
			SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 0xFF, 0xFF));

			// create texture from pixels
			texture = SDL_CreateTextureFromSurface(Renderer::get(), newSurface);

			if (!texture)
				std::cout << "Unable to create texture: " << retryPath.c_str() << " " << SDL_GetError() << "\n";

			// get rid of loaded surface
			SDL_FreeSurface(newSurface);
		}
		return texture;
	}

}
