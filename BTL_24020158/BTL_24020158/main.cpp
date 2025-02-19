#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
struct object{
    SDL_Rect rect;
    int dx = 0,dy = 0;
    void move(){
        rect.x+=dx;
        rect.y+=dy;
    }
};
int playerspeed = 5;
int enemiesspeed = 2;

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

int main(){
    SDL_INIT_VIDEO;
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_CreateWindowAndRenderer(640*2, 480*2, SDL_WINDOW_SHOWN, &window, &render);
    
    vector <object> enemies;
    vector <object>::iterator it;
    vector <object> bullets;
    vector <object>::iterator it2;
    
    object player;
    player.rect = {640 , 480 , 50 , 50};
//    object* mark;
    
    srand(time(0));
    // chua co code xoa sau khi ra khoi man hinh
    bool running = true;
    SDL_Event event;
    while (running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_UP){
                    player.dy = -playerspeed;
                }
                if (event.key.keysym.sym == SDLK_DOWN){
                    player.dy = playerspeed;
                }
                if (event.key.keysym.sym == SDLK_RIGHT){
                    player.dx = playerspeed;
                }
                if (event.key.keysym.sym == SDLK_LEFT){
                    player.dx = -playerspeed;
                }
                if (event.key.keysym.sym == SDLK_SPACE){
                    object ex_bullet = {player.rect.x + 23 , player.rect.y , 10 , 10};
                    bullets.push_back(ex_bullet);
                }
                
            }
            if (event.type == SDL_KEYUP){
                player.dx = 0;
                player.dy = 0;
            }
            
        }
        if (player.rect.x <0 && player.dx <0 ){
            player.dx=0;
        }
        if (player.rect.x > 640*2-50 && player.dx >0 ){
            player.dx=0;
        }
        if (player.rect.y <0 && player.dy <0 ){
            player.dy=0;
        }
        if (player.rect.y > 480*2-50 && player.dy >0 ){
            player.dy=0;
        }
        player.move();
        
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        
//           if (enemies.rect.y > 480*2) {enemies.rect.y=0;};
        SDL_SetRenderDrawColor(render, 216, 249, 10, 1);
        SDL_RenderFillRect(render, &player.rect);
        
        if (rand()%30 == 5){  // Sinh ngẫu nhiên enemies
            object doithu;
            doithu.rect = {rand()%640*2 , -40 , 50 , 50};
            enemies.push_back(doithu);
        }
        SDL_SetRenderDrawColor(render, 173, 26, 28, 1);
        for (it=enemies.begin(); it!=enemies.end(); it++){
            it->rect.y+=2;   // Chỉnh tốc độ của enemies
            SDL_RenderFillRect(render, &it->rect);
            if (it->rect.y>480*2) { enemies.erase(it);};
        }
        SDL_SetRenderDrawColor(render, 255, 126, 0, 1);
        for (it2=bullets.begin(); it2!=bullets.end(); it2++){
            it2->rect.y-=2;   // Chỉnh tốc độ của bullets
            SDL_RenderFillRect(render, &it2->rect);
            if (it2->rect.y<0) { bullets.erase(it2);};
        }
        
        
        for (it2 = bullets.begin(); it2!=bullets.end(); ){
            bool chek = true;
            for (it = enemies.begin(); it!=enemies.end(); ){
                if (SDL_HasIntersection(&it->rect, &it2->rect)){
                    it = enemies.erase(it);
                    it2 = bullets.erase(it2);
                    chek=false;
                    break;
                }
                else {
                    ++it;
                }
            }
            if (chek) {
                ++it2;
            }
        }
        
        
        
    
                
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    
    
    
    return 0;
}
