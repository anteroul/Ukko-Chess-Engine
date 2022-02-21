#ifndef UKKOSHAKKI_FONTLOADER_H
#define UKKOSHAKKI_FONTLOADER_H

#include "Global.hh"
#include <iostream>

namespace FontLoader {
	TTF_Font* loadFont(std::string path, int fontSize);
}

#endif //UKKOSHAKKI_FONTLOADER_H
