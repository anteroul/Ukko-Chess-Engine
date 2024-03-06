#include "Window.hh"

Window::Window() : renderer(Renderer())
{
	// get monitor resolution
	// SDL_DisplayMode mode;
	// SDL_GetCurrentDisplayMode(0, &mode);

	// Set width and height
	width = 800;
	height = 600;

	// store screen sizes
	setSizes();

	// create window
	window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
							  SDL_WINDOW_RESIZABLE);

	// if window creation fails
	if (!window)
		std::cout << "Could not create window! " << SDL_GetError() << "\n";
	else
	{
		renderer = Renderer(*window);
	}
}

void Window::resize(SDL_Event e)
{
	switch (e.type)
	{
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				// get new screensize and set it accordingly
				SDL_GetWindowSize(window, &width, &height);
				setSizes();
			}
			break;
	}
}

void Window::setSizes() const
{
	Screen::setWidth(width);
	Screen::setHeight(height);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer.renderer);
	SDL_DestroyWindow(window);
}

