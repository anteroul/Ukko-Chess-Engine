#include "Button.hh"

Button::Button(PieceFactory* factory, Type value)
{
	icon = factory->getButton(0);

	x = Screen::getWidth();
	y = Screen::getHeight() / 2;
	w = Screen::getWidth() / 8;
	h = Screen::getHeight() / 6;

	switch (value)
	{
		case BISHOP:
			if (Global::playerTurn)
			{
				icon = factory->getButton(4);
			} else {
				icon = factory->getButton(0);
			}
			break;
		case KNIGHT:
			if (Global::playerTurn)
			{
				icon = factory->getButton(5);
			} else {
				icon = factory->getButton(1);
			}
			break;
		case QUEEN:
			if (Global::playerTurn)
			{
				icon = factory->getButton(6);
			} else {
				icon = factory->getButton(2);
			}
			break;
		case ROOK:
			if (Global::playerTurn)
			{
				icon = factory->getButton(7);
			} else {
				icon = factory->getButton(3);
			}
			break;
		default:
			break;
	}
}

SDL_Texture *Button::getButtonTexture()
{
	return icon;
}

SDL_Rect Button::getRect()
{
	return { x, y, w, h };
}