#include "PieceFactory.hh"

PieceFactory::PieceFactory(Renderer& ren) : ren(ren)
{
	for (int i = 0; i < ARRSIZE(p); i++)
	{
		if (Texture::load(c[i], ren))
			p[i] = Texture::load(c[i], ren);
		else
			p[i] = Texture::load("../" + c[i], ren);
	}
}

PieceFactory::~PieceFactory()
{
	for (auto &i: p) SDL_DestroyTexture(i);
}

SDL_Texture *PieceFactory::getPiece(int n)
{ return p[n]; }
