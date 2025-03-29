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
#include <fstream>


const int MAX_SCREEN_WEIGHT = 800;
const int MAX_SCREEN_HEIGHT = 600;
const int HIGH_SCORE_X = MAX_SCREEN_HEIGHT - 90;
const int HIGH_SCORE_Y = 50;
const int HIGH_YOUR_SCORE_SPACE = 50;
const int PLAYER_INIT_X = MAX_SCREEN_WEIGHT/2 - 148/2;
const int PLAYER_INIT_Y = MAX_SCREEN_HEIGHT - 145 - 158/2 + 5;
const int PLAYER_SPEED = 5;
const int ENEMIES_SPEED = 2;
const int Enemies_gen_num = 5;
const int BOOST_ENE_SPEED = 8;
const int WAVE_SPEED = 3;
// player_hight = 158, player_width = 148

const char GameName[] = "Claim your efforts";
const char GameBackground_PATH[] = "src/background.png";
const char MenuBackground_PATH[] = "src/menu_background.png";
const char MenuInstruction_PATH[] = "src/instruction.png";
const char Play_againBackground_PATH[] = "src/play_again.png";
const char Font_PATH[] = "font/pixel_font.ttf";
const char Player_PATH[] = "src/player.png";
const char WHITE_ENE_PATH[] = "src/white.png";
const char YELLOW_ENE_PATH[] = "src/yellow.png";
const char ICON_PATH[] = "src/yellow.png";
const char BOOST_ENE_PATH[] = "src/boost.png";
const char WAVE_PATH[] = "src/wave.png";
const char BLOOD_ON[] = "src/blood_on.png";
const char BLOOD_OFF[] = "src/blood_off.png";
const char PLAY_BTN_PATH[] = "src/btn/play_button.png";
const char HELP_BTN_PATH[] = "src/btn/help_button.png";
const char PAUSE_BTN_PATH[] = "src/btn/pause_button.png";
const char CONTINUE_BTN_PATH[] = "src/btn/continue_button.png";

const char MENU_CLICK_PATH[] = "sound/menu_button.wav";
const char LOSE_SOUND_PATH[] = "sound/game_over.wav";
const char GAME_START_PATH[] = "sound/game_start.wav";
const char WHITE_ENE_COLL_PATH[] = "sound/white_ene_coll.wav";
const char YELLOW_ENE_COLL_PATH[] = "sound/yellow_ene_coll.wav";
const char MENU_MUSIC_PATH[] = "sound/menu_music.wav";
const char BKGR_MUSIC_PATH[] = "sound/bkgr_audio.wav";

#endif /* GameBase_h */
