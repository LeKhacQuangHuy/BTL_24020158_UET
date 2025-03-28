//
//  GameUltis.c
//  Learning
//
//  Created by Huy Le's Macbook on 28/2/25.
//

#include "GameUltis.h"
#include "GameBase.h"
using namespace std;
int getRandomNum(int a, int b){
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution card{a, b};
    return card(mt);
}
void renderIMG(SDL_Texture* texture, SDL_Renderer* gRenderer, SDL_Rect rect){
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);
}
bool checkCollision(SDL_Rect player_rect, SDL_Rect enemies_rect){
//    player_rect.h = player_rect.h * 0.1;
    return SDL_HasIntersection(&player_rect, &enemies_rect);
}
bool handle_delay_action(Uint32 start_time, int time){
    if (SDL_GetTicks() - start_time <= time * 100){
        return true;
    }
    return false;
}
std::string high_score_num(int new_high_score , int & MAX_SCORE){
    ifstream load_data;
    load_data.open("/Users/huylesmacbook/Library/Developer/Xcode/DerivedData/Learning-cdhyvssvqcagzrfkuqtdpvnnerph/Build/Products/Debug/Learning.app/Contents/Resources/saved_high_score.txt");
    if (!load_data.is_open()){
        cout << "Failed to load high score";
    }
    int old_high_score = 0;
    load_data >> old_high_score;
    cout << old_high_score;
    load_data.close();
    if (MAX_SCORE < old_high_score){
        MAX_SCORE = old_high_score;
    }
    if (new_high_score > MAX_SCORE){
        MAX_SCORE = new_high_score;
        
    }
    return to_string(MAX_SCORE);
}


