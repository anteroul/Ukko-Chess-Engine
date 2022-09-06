#include "PieceFactory.hh"

PieceFactory::PieceFactory()
{
	for (int i = 0; i < ARRSIZE(p); i++)
	{
		if (Texture::load(c[i]))
			p[i] = Texture::load(c[i]);
		else
			p[i] = Texture::load("../" + c[i]);
	}
	for (int i = 0; i < ARRSIZE(b); i++)
	{
		if (Texture::load(btn_src[i]))
			b[i] = Texture::load(btn_src[i]);
		else
			b[i] = Texture::load("../" + c[i]);
	}
}

PieceFactory::~PieceFactory()
{
	for (auto &i: p) SDL_DestroyTexture(i);
	for (auto &i: b) SDL_DestroyTexture(i);
}

SDL_Texture *PieceFactory::getPiece(int n)
{ return p[n]; }

SDL_Texture *PieceFactory::getButton(int n)
{ return b[n]; }

