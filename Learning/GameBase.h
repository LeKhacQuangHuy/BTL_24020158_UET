//
//  GameBase.h
//  Learning
//
//  Created by Huy Le's Macbook on 28/2/25.
//

#ifndef GameBase_h
#define GameBase_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>
#include <random>
#include <vector>



const int MAX_SCREEN_WEIGHT = 800;
const int MAX_SCREEN_HEIGHT = 600;
const int HIGH_SCORE_X = MAX_SCREEN_HEIGHT - 50;
const int HIGH_SCORE_Y = 50;
const int HIGH_YOUR_SCORE_SPACE = 50;
const int PLAYER_INIT_X = MAX_SCREEN_WEIGHT/2 - 148/2;
const int PLAYER_INIT_Y = MAX_SCREEN_HEIGHT - 145 - 158/2;
const int PLAYER_SPEED = 5;
const int ENEMIES_SPEED = 2;
const int Enemies_gen_num = 5;
// player_hight = 158, player_width = 148

const char GameName[] = "Learning";
const char GameBackground_PATH[] = "src/background.png";
const char Font_PATH[] = "font/pixel_font.ttf";
const char Player_PATH[] = "src/player.png";
const char WHITE_ENE_PATH[] = "src/white.png";
const char YELLOW_ENE_PATH[] = "src/yellow.png";
const char ICON_PATH[] = "src/yellow.png";


#endif /* GameBase_h */
