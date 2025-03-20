//
//  GamePlayer.h
//  Learning
//
//  Created by Huy Le's Macbook on 12/3/25.
//

#ifndef GameObject_h
#define GameObject_h

#include <stdio.h>
#include "GameBase.h"
#include "GameUltis.h"
#include "LTexture.h"
//#include "main.h"

static Mix_Chunk* lChunk = nullptr;

struct object{
    const Uint8 * keystate = SDL_GetKeyboardState(nullptr);
    int x = 0,y = 0;
    SDL_Texture* objectTexture = nullptr;
//    LTexture objectLoadTexture;
    SDL_Rect objectRect;
    //Create rect when calling
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    void load_audio(Mix_Chunk* gChunk){
        lChunk = gChunk;
    }

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

static std::vector <object> white_enemies;
static std::vector <object> yellow_enemies;
static std::vector <object>::iterator it;

static LTexture lLoader;

struct enemies{
    void gen_new_enemies(int num_of_ene, object enemy_type, SDL_Renderer* gRenderer, std::string pic_PATH){
        int init_x = getRandomNum(0, MAX_SCREEN_WEIGHT);
        int init_y = getRandomNum(-50, -5);
        for (int i = 0; i < num_of_ene; ++i){
            if (pic_PATH.find("white") != std::string::npos){
                white_enemies.push_back(std::move(enemy_type));
                white_enemies.back().objectTexture = lLoader.load_pic_from_file(pic_PATH, gRenderer);
                white_enemies.back().objectRect = lLoader.create_rect(white_enemies.back().objectTexture, init_x, init_y);
            }
            else{
                yellow_enemies.push_back(std::move(enemy_type));
                yellow_enemies.back().objectTexture = lLoader.load_pic_from_file(pic_PATH, gRenderer);
                yellow_enemies.back().objectRect = lLoader.create_rect(yellow_enemies.back().objectTexture, init_x, init_y);
            }
            
        }
    }
    int handle_white_enemies(object player){
        //White
        int res = 0;
        bool chek1 = false;
        bool chek2 = false;
        for (it = white_enemies.begin(); it != white_enemies.end();){
            it->objectRect.y+= ENEMIES_SPEED;   // Chỉnh tốc độ của enemies
            if (it->objectRect.y > MAX_SCREEN_HEIGHT)
            {
                SDL_DestroyTexture(it->objectTexture);
                it = white_enemies.erase(it);
                chek1 = true;
            }
            
            if (checkCollision(player.objectRect, it->objectRect)){
                res = 1;
                SDL_DestroyTexture(it->objectTexture);
                it = white_enemies.erase(it);
                chek2 = true;
            }
            
            if (chek1 == false && chek2 == false){
                ++it;
            }
            
            chek1 = false;
            chek2 = false;
            
        }
        return res;
    }
    
    int handle_yellow_enemies(object player){
        //Yellow
        int res = 0;
        bool chek1 = false;
        for (it = yellow_enemies.begin(); it != yellow_enemies.end();){
            it->objectRect.y+=2;   // Chỉnh tốc độ của enemies
            if (it->objectRect.y > MAX_SCREEN_HEIGHT)
            {
                SDL_DestroyTexture(it->objectTexture);
                it = yellow_enemies.erase(it);
                chek1 = true;
            }
            if (checkCollision(player.objectRect, it->objectRect)){
                res = 1;
            }
            if (chek1 == false){
                ++it;
            }
            chek1 = false;
        }
        return res;
    }
    
    
    
    void render(SDL_Texture* texture, SDL_Renderer* gRenderer){
        for (it = white_enemies.begin(); it != white_enemies.end(); ++it){
            SDL_RenderCopy(gRenderer, it->objectTexture, NULL, &it->objectRect);
        }
        for (it = yellow_enemies.begin(); it != yellow_enemies.end(); ++it){
            renderIMG(it->objectTexture, gRenderer, it->objectRect);
        }
    }
    void reset(){
        for (it = white_enemies.begin(); it != white_enemies.end(); ){
            SDL_DestroyTexture(it->objectTexture);
            it = white_enemies.erase(it);
        }
        for (it = yellow_enemies.begin(); it != yellow_enemies.end(); ){
            SDL_DestroyTexture(it->objectTexture);
            it = yellow_enemies.erase(it);
        }
    }
    
};

#endif /* GameObject_h */
