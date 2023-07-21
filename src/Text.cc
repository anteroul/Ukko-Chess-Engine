#include <utility>
#include "Text.hh"


Text::Text(std::string _text, bool playerTurn) : text(std::move(_text))
{
	font = FontLoader::loadFont("Assets/Fonts/mytype.ttf", 14);
	if (!playerTurn)
		color = { 0, 255, 255, 255 };
	else
		color = { 255, 255, 0, 255 };

	position.x = Screen::getWidth() - 150;
	position.y = Screen::getHeight() - 25;

	if (font)
		setText();
	else
		std::cout << "Error loading font! " << TTF_GetError << "\n";
}

Text::Text(std::string _text, float width, float height)
{
    font = FontLoader::loadFont("Assets/Fonts/mytype.ttf", 14);
    color = { 255, 255, 0, 255 };
    position.x = Screen::getWidth() * width;
    position.y = Screen::getHeight() * height;

    if (font)
        setText();
    else
        std::cout << "Error loading font! " << TTF_GetError << "\n";
}

Text::~Text()
{
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void Text::setText()
{
	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(Renderer::get(), surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &position.w, &position.h);
}

void Text::render()
{
	position.x = Screen::getWidth() - Screen::getWidth() / 5;
	SDL_RenderCopy(Renderer::get(), textTexture, nullptr, &position);
}

