//
//  GameUltis.h
//  Learning
//
//  Created by Huy Le's Macbook on 28/2/25.
//

#ifndef GameUltis_h
#define GameUltis_h

#include <stdio.h>
#include "GameBase.h"

bool init();
bool loadmedia();
//SDL_Texture* loadTexture( std::string path );
void close();
void draw_high_score();
void draw_your_score();
void draw_player();

#endif /* GameUltis_h */
