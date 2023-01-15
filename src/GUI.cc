#include "GUI.hh"

bool GUI::onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square)
{
	return SDL_PointInRect(&mousePos, &square);
}

Square *GUI::onSelect(SDL_Point &mousePos)
{
	int x = mousePos.x * 10 / Screen::getWidth();
	int y = mousePos.y * 8 / Screen::getHeight();

	if (Sqr::squareHelper(x, y) != nullptr)
		return &Sqr::getSquare(x, y);
	else
		return &Sqr::getSquare(7, y);
}

void GUI::displayPromotionTable(const std::vector<Button*> &btn)
{
	auto rect = new SDL_Rect {Screen::getWidth() / 8, Screen::getHeight() / 5, static_cast<int>(Screen::getWidth() * 0.75f), Screen::getHeight() / 2};

	SDL_SetRenderDrawColor(Renderer::get(), 128, 128, 128, 255);
	SDL_RenderFillRect(Renderer::get(), rect);

	for (auto & i : btn)
	{
		SDL_Rect r = i->getRect();
		SDL_RenderCopy(Renderer::get(), i->getButtonTexture(), nullptr, &r);
	}
}