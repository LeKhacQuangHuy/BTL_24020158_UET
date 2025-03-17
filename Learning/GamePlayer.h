//
//  GamePlayer.h
//  Learning
//
//  Created by Huy Le's Macbook on 12/3/25.
//

#ifndef GamePlayer_h
#define GamePlayer_h

#include <stdio.h>
#include "GameBase.h"
#include "GameUltis.h"
#include "LTexture.h"
struct object{
    const Uint8 * keystate = SDL_GetKeyboardState(nullptr);
    int x = 0,y = 0;
    SDL_Texture* objectTexture = nullptr;
    LTexture objectLoadTexture;
    SDL_Rect objectRect;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
//    SDL_Rect objectRect
//    int dx=0, dy=0;
    void move_right(){
        if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]){
            objectRect.x += PLAYER_SPEED;
            flip = SDL_FLIP_NONE;
            
        }
    }
    void move_left(){
        if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]){
            objectRect.x -= PLAYER_SPEED;
            flip = SDL_FLIP_HORIZONTAL;
        }
    }
    void update(){
        if (objectRect.x < -30){
            move_right();
        }
        if (objectRect.x > MAX_SCREEN_WEIGHT - 100){
            move_left();
        }
        if (objectRect.x >= -30 && objectRect.x <= MAX_SCREEN_WEIGHT - 100){
            move_right();
            move_left();
        }
    }
};

#endif /* GamePlayer_h */
