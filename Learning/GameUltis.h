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
int getRandomNum(int a, int b);
void renderIMG(SDL_Texture* texture, SDL_Renderer* gRenderer, SDL_Rect rect);
bool checkCollision(SDL_Rect rect_a, SDL_Rect rect_b);
#endif /* GameUltis_h */
