#include "GameManager.hh"

namespace GameManager
{
	void update()
	{
		Global::playerCanCastleK = true;
		Global::playerCanCastleQ = true;
		Global::playerInCheck = false;
	
		Global::engineCanCastleK = true;
		Global::engineCanCastleQ = true;
		Global::engineInCheck = false;

		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(Sqr::squareHelper(i, j)->piece->user == ENGINE)
				{
					std::vector<Square> v = LegalMove::get(*Sqr::squareHelper(i, j)->piece);
					
					for(auto& k : v)
					{
						// king is in check
						if(k.piece->type == 5)
						{
							Global::playerInCheck = true;
							Global::playerCanCastleQ = false;
							Global::playerCanCastleK = false;
						}

						// possibility to castle
						if(!Global::playerKingMoved)
						{
							if(!Global::playerKsideRookMoved)
							{
								if((k.x == 5 && k.y == 7) || (k.x == 6 && k.y == 7))
									Global::playerCanCastleK = false;
							}
							else
								Global::playerCanCastleK = false;
							
							if(!Global::playerQsideRookMoved)
							{
								if((k.x == 1 && k.y == 7) || (k.x == 2 && k.y == 7))
									Global::playerCanCastleQ = false;
							}
							else
								Global::playerCanCastleQ = false;
						}
						else
						{
							Global::playerCanCastleQ = false;
							Global::playerCanCastleK = false;
						}
					}
					
				}

				if(Sqr::squareHelper(i, j)->piece->user == PLAYER)
				{
					std::vector<Square> v = LegalMove::get(*Sqr::squareHelper(i, j)->piece);

					for(auto& k : v)
					{
						// see checks
						if(k.piece->type == 5)
						{
							Global::engineInCheck = true;
							Global::engineCanCastleK = false;
							Global::engineCanCastleQ = false;
						}

						// possibility to castle
						if(!Global::engineKingMoved)
						{
							if(!Global::engineKsideRookMoved)
							{
								if((k.x == 5 && k.y == 0) || (k.x == 6 && k.y == 7))
									Global::engineCanCastleK = false;
							}
							else
								Global::engineCanCastleK = false;

							if(!Global::engineQsideRookMoved)
							{
								if((k.x == 1  && k.y == 0) || (k.x == 2 && k.y == 0))
									Global::playerCanCastleQ = false;
							}
							else
								Global::engineCanCastleQ = false;

						}
						else
						{
							Global::engineCanCastleK = false;
							Global::engineCanCastleQ = false;
						}
					}
				}
			}
		}
	}
}
