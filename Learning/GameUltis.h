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

static int handle_delay_num = 0;

bool init();
bool loadmedia();
//SDL_Texture* loadTexture( std::string path );
void close();
void draw_high_score();
void draw_your_score(int score);
void draw_player();
int getRandomNum(int a, int b);
void renderIMG(SDL_Texture* texture, SDL_Renderer* gRenderer, SDL_Rect rect);
bool checkCollision(SDL_Rect rect_a, SDL_Rect rect_b);
void show_lose_screen(bool &play_Again);
void show_bonus_score(int x, int y);
bool handle_delay_action(Uint32 start_time, int time);
std::string high_score_num(int new_high_score, int & MAX_SCORE);
#endif /* GameUltis_h */
