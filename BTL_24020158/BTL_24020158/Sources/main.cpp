#include "GameBase.hpp"
//#include "ultility.h"
using namespace std;
struct object{
    SDL_Rect rect;
    int dx = 0,dy = 0;
    void move(){
        rect.x+=dx;
        rect.y+=dy;
    }
};
const int playerspeed = 5;
const int enemiesspeed = 2;
const int MAX_SCREEN_WIDTH = 414;
const int MAX_SREEEN_HEIGHT = 736;

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

SDL_Texture* loadBackground(const char* filePath, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if (!tempSurface) {
        std::cerr << "Lỗi tải ảnh: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        std::cerr << "Lỗi tạo texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_CreateWindowAndRenderer(MAX_SCREEN_WIDTH, MAX_SREEEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &render);
    SDL_Texture* background = loadBackground("Res/pic.jpg", render);
    
    vector <object> enemies;
    vector <object>::iterator it;
    vector <object> bullets;
    vector <object>::iterator it2;
    
    object player;
    player.rect = {MAX_SCREEN_WIDTH/2 , MAX_SREEEN_HEIGHT/2 , 50 , 50};
//    object* mark;
    
    srand(time(NULL));
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
        if (player.rect.x > MAX_SCREEN_WIDTH-50 && player.dx >0 ){
            player.dx=0;
        }
        if (player.rect.y <0 && player.dy <0 ){
            player.dy=0;
        }
        if (player.rect.y > MAX_SREEEN_HEIGHT-50 && player.dy >0 ){
            player.dy=0;
        }
        player.move();
        
        
//        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        SDL_RenderCopy(render, background, NULL, NULL);
        
//           if (enemies.rect.y > 480*2) {enemies.rect.y=0;};
        SDL_SetRenderDrawColor(render, 216, 249, 10, 1);
        SDL_RenderFillRect(render, &player.rect);
        
        if (rand()%30 == 0){  // Sinh ngẫu nhiên enemies
            object doithu;
            doithu.rect = {rand()% (MAX_SCREEN_WIDTH - 50 -50 +1) + 50 , -40 , 50 , 50};
            enemies.push_back(doithu);
        }
        SDL_SetRenderDrawColor(render, 173, 26, 28, 1);
        for (it=enemies.begin(); it!=enemies.end();){
            it->rect.y+=2;   // Chỉnh tốc độ của enemies
            SDL_RenderFillRect(render, &it->rect);
            if (it->rect.y>MAX_SREEEN_HEIGHT)
            {
                it = enemies.erase(it);
            } else
                ++it;
        }
        
        SDL_SetRenderDrawColor(render, 255, 126, 0, 1);
        for (it2=bullets.begin(); it2!=bullets.end(); ){
            it2->rect.y-=2;   // Chỉnh tốc độ của bullets
            SDL_RenderFillRect(render, &it2->rect);
            if (it2->rect.y<0) {
                it2 = bullets.erase(it2);
            } else ++it2;
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
        SDL_Delay(20);
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    IMG_Quit();
    SDL_DestroyTexture(background);

    
    
    return 0;
}
