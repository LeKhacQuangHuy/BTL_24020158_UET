//
//  LTexture.h
//  Learning
//
//  Created by Huy Le's Macbook on 6/3/25.
//

#ifndef LTexture_h
#define LTexture_h

#include <stdio.h>
#include "GameBase.h"

struct LTexture
{
    SDL_Texture* load_pic_from_file(std::string FILE_PATH, SDL_Renderer* gRenderer);
    SDL_Texture* load_text(std::string TEXT_PATH, std::string TEXT2LOAD, SDL_Renderer* gRenderer);
    
    SDL_Rect create_rect(SDL_Texture* texture, int x, int y);
};

#endif /* LTexture_h */




