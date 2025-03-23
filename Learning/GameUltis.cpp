//
//  GameUltis.c
//  Learning
//
//  Created by Huy Le's Macbook on 28/2/25.
//

#include "GameUltis.h"
#include "GameBase.h"
int getRandomNum(int a, int b){
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution card{a, b};
    return card(mt);
}
void renderIMG(SDL_Texture* texture, SDL_Renderer* gRenderer, SDL_Rect rect){
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);
}
bool checkCollision(SDL_Rect player_rect, SDL_Rect enemies_rect){
//    player_rect.w = player_rect.w * 0.6;
    return SDL_HasIntersection(&player_rect, &enemies_rect);
}
bool handle_delay_action(Uint32 start_time, int time){
    if (SDL_GetTicks() - start_time <= time * 100){
        return true;
    }
    return false;
}
