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
static Mix_Chunk* lChunk_bonus = nullptr;


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
        if (keystate[SDL_SCANCODE_RIGHT]){
            objectRect.x += PLAYER_SPEED;
            flip = SDL_FLIP_NONE;
            
        }
        if (keystate[SDL_SCANCODE_D]){
            objectRect.x += PLAYER_SPEED;
            flip = SDL_FLIP_NONE;
        }
    }
    void move_left(){
        if (keystate[SDL_SCANCODE_LEFT]){
            objectRect.x -= PLAYER_SPEED;
            flip = SDL_FLIP_HORIZONTAL;
            
        }
        if ( keystate[SDL_SCANCODE_A]){
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
static std::vector <object> boost_enemies;
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
                if (white_enemies.back().objectTexture == NULL){
                    std::cout << "Can't load white enemies" << std::endl;
                }
                white_enemies.back().objectRect = lLoader.create_rect(white_enemies.back().objectTexture, init_x, init_y);
            }
            if (pic_PATH.find("yellow") != std::string::npos){
                yellow_enemies.push_back(std::move(enemy_type));
                yellow_enemies.back().objectTexture = lLoader.load_pic_from_file(pic_PATH, gRenderer);
                if (yellow_enemies.back().objectTexture == NULL){
                    std::cout << "Can't load yellow enemies" << std::endl;
                }
                yellow_enemies.back().objectRect = lLoader.create_rect(yellow_enemies.back().objectTexture, init_x, init_y);
                yellow_enemies.back().objectRect.w *= 1.5;
                yellow_enemies.back().objectRect.h *= 1.5;
            }
            if (pic_PATH.find("boost") != std::string::npos){
                boost_enemies.push_back(std::move(enemy_type));
                boost_enemies.back().objectTexture = lLoader.load_pic_from_file(pic_PATH, gRenderer);
                if (boost_enemies.back().objectTexture == NULL){
                    std::cout << "Can't load boost enemies" << std::endl;
                }
                boost_enemies.back().objectRect = lLoader.create_rect(boost_enemies.back().objectTexture, init_x, init_y);
                boost_enemies.back().objectRect.w *= 0.9;
                boost_enemies.back().objectRect.h *= 0.9;
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
                Mix_FreeChunk(lChunk);
                lChunk = Mix_LoadWAV(WHITE_ENE_COLL_PATH);
                if (lChunk == NULL){
                    std::cout << "Failed to load chunk sound";
                }
                Mix_PlayChannel(-1, lChunk, 0);
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
        bool chek1 = false, chek2 = false;
        for (it = yellow_enemies.begin(); it != yellow_enemies.end();){
            it->objectRect.y+=2;   // Chỉnh tốc độ của enemies
            if (it->objectRect.y > MAX_SCREEN_HEIGHT)
            {
                SDL_DestroyTexture(it->objectTexture);
                it = yellow_enemies.erase(it);
                chek1 = true;
            }
            if (checkCollision(player.objectRect, it->objectRect)){
                Mix_FreeChunk(lChunk);
                lChunk = Mix_LoadWAV(YELLOW_ENE_COLL_PATH);
                if (lChunk == NULL){
                    std::cout << "Failed to load chunk sound";
                }
                Mix_PlayChannel(-1, lChunk, 0);
                SDL_DestroyTexture(it->objectTexture);
                it = yellow_enemies.erase(it);
                chek2 = true;
                res = 1;
            }
            if (chek1 == false && chek2 == false){
                ++it;
            }
            chek1 = false;
            chek2 = false;
        }
        return res;
    }
    int handle_boost_enemies(object player){
        //White
        int res = 0;
        bool chek1 = false;
        bool chek2 = false;
        for (it = boost_enemies.begin(); it != boost_enemies.end();){
            it->objectRect.y+= BOOST_ENE_SPEED;   // Chỉnh tốc độ của enemies
            if (it->objectRect.y > MAX_SCREEN_HEIGHT)
            {
                SDL_DestroyTexture(it->objectTexture);
                it = boost_enemies.erase(it);
                chek1 = true;
            }
            
            if (checkCollision(player.objectRect, it->objectRect)){
                res = 1;
                Mix_FreeChunk(lChunk_bonus);
                lChunk_bonus = Mix_LoadWAV("sound/bonus_sound.wav");
                if (lChunk_bonus == NULL){
                    std::cout << "Failed to load bonus chunk sound";
                }
                Mix_PlayChannel(0, lChunk_bonus, 0);
                SDL_DestroyTexture(it->objectTexture);
                it = boost_enemies.erase(it);
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
    
    
    void render(SDL_Texture* texture, SDL_Renderer* gRenderer, std::string OBJECT_TO_RENDER){
        if (OBJECT_TO_RENDER.find("white") != std::string::npos){
            for (it = white_enemies.begin(); it != white_enemies.end(); ++it){
                SDL_RenderCopy(gRenderer, it->objectTexture, NULL, &it->objectRect);
            }
        }
        if (OBJECT_TO_RENDER.find("yellow") != std::string::npos){
            for (it = yellow_enemies.begin(); it != yellow_enemies.end(); ++it){
                renderIMG(it->objectTexture, gRenderer, it->objectRect);
            }
        }
        if (OBJECT_TO_RENDER.find("boost") != std::string::npos){
            for (it = boost_enemies.begin(); it != boost_enemies.end(); ++it){
                renderIMG(it->objectTexture, gRenderer, it->objectRect);
            }
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
        for (it = boost_enemies.begin(); it != boost_enemies.end(); ){
            SDL_DestroyTexture(it->objectTexture);
            it = boost_enemies.erase(it);
        }

    }
    
};


static std::vector <object> blood_enemies;


struct blood_object{
    bool load_blood_on(SDL_Renderer* gRenderer){
        bool success = true;
        for (int i = 0; i < 5; ++i){
            blood_enemies.emplace_back();
            blood_enemies.back().objectTexture = lLoader.load_pic_from_file(BLOOD_ON, gRenderer);
            blood_enemies.back().objectRect = lLoader.create_rect(blood_enemies.back().objectTexture, HIGH_SCORE_X + i*30 ,HIGH_SCORE_Y + HIGH_YOUR_SCORE_SPACE*2 );
            blood_enemies.back().objectRect.w *= 0.5;
            blood_enemies.back().objectRect.h *= 0.5;
            if (blood_enemies.back().objectTexture == NULL){
                std::cout << "Failed to load blood_on" << std::endl;
                return false;
            }
        }
        return success;
    }
    void blood_handle(int blood_remain, SDL_Renderer* gRenderer){
        if (blood_remain >= 1){
            it = blood_enemies.end();
            (it - (5 - blood_remain))->objectTexture = lLoader.load_pic_from_file(BLOOD_OFF, gRenderer);
        }
    }

    void draw_blood(SDL_Renderer* gRenderer){
        for (it = blood_enemies.begin(); it != blood_enemies.end(); ++it){
            SDL_RenderCopy(gRenderer, it->objectTexture, NULL, &it->objectRect);
        }
    }
    void reset(SDL_Renderer* gRenderer){
        for (it = blood_enemies.begin(); it != blood_enemies.end();){
            SDL_DestroyTexture(it->objectTexture);
            it = blood_enemies.erase(it);
        }
        for (int i = 0; i < 5; ++i){
            blood_enemies.emplace_back();
            blood_enemies.back().objectTexture = lLoader.load_pic_from_file(BLOOD_ON, gRenderer);
            blood_enemies.back().objectRect = lLoader.create_rect(blood_enemies.back().objectTexture, HIGH_SCORE_X + i*30 ,HIGH_SCORE_Y + HIGH_YOUR_SCORE_SPACE*2 );
            blood_enemies.back().objectRect.w *= 0.5;
            blood_enemies.back().objectRect.h *= 0.5;
        }
    }

};

#endif /* GameObject_h */
