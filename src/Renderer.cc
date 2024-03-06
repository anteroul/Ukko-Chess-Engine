#include "Renderer.hh"

Renderer::Renderer(SDL_Window& window)
{
	// create the renderer
	renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		std::cout << "Could not create renderer! " << SDL_GetError() << "\n";
	else
	{
		// set the renderer
		set(renderer);
	}
}

// setter and getter
void Renderer::set(SDL_Renderer *_renderer)
{ renderer = _renderer; }

// render functions
void Renderer::setColor(int r, int g, int b) const
{ SDL_SetRenderDrawColor(renderer, r, g, b, 255); }

void Renderer::clear() const
{ SDL_RenderClear(renderer); }

void Renderer::render() const
{ SDL_RenderPresent(renderer); }

void Renderer::fillRect(SDL_Rect r) const
{ SDL_RenderFillRect(renderer, &r); }
