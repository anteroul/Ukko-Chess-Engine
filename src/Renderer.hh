#ifndef RENDERER_HH
#define RENDERER_HH

#include <SDL2/SDL.h>
#include <iostream>

class Renderer
{
public:
	Renderer() = default;
	explicit Renderer(SDL_Window& window);
	void set(SDL_Renderer* _renderer);
	void setColor(int r, int g, int b) const;
	void clear() const;
	void render() const;
	void fillRect(SDL_Rect r) const;
	SDL_Renderer* renderer;
};

#endif
