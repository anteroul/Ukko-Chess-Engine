#include "Board.hh"

Board::Board(Window &win)
{
	renderer = win.getRenderer();
}

void Board::makeBoard() const
{
	// width and height of single tile
	auto width = srcrect.w / 10 / 8 * 0.8f;
	auto height = srcrect.h / 10 / 8;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// make all squares
			Sqr::getSquare(i, j).rect.x = i * width;
			Sqr::getSquare(i, j).rect.y = j * height;
			Sqr::getSquare(i, j).rect.w = width;
			Sqr::getSquare(i, j).rect.h = height;

			// x and y positions to squares
			Sqr::getSquare(i, j).x = i;
			Sqr::getSquare(i, j).y = j;

			// different colors to every other square
			if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0))
			{
				renderer->setColor(64, 48, 0);
				renderer->fillRect(Sqr::getSquare(i, j).rect);
			} else {
				renderer->setColor(128, 64, 0);
				renderer->fillRect(Sqr::getSquare(i, j).rect);
			}
		}
	}
}

void Board::makeRects()
{
	srcrect.x = 0;
	srcrect.y = 0;

	// make source bigger than screen size so the source will be the size of the window
	srcrect.w = Screen::getWidth() * 10;
	srcrect.h = Screen::getHeight() * 10;

	dstrect.x = 0;
	dstrect.y = 0;

	// leave space on the right
	dstrect.w = Screen::getWidth() / 5 * 4;
	dstrect.h = Screen::getHeight();
}

void Board::render()
{
	// update rects
	makeRects();

	// update board
	makeBoard();
}

