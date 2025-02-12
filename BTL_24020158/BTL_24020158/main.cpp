#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
struct object{
    SDL_Rect rect;
    int dx,dy;
};

int main(){
    SDL_INIT_VIDEO;
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_CreateWindowAndRenderer(640*2, 480*2, SDL_WINDOW_SHOWN, &window, &render);
    
    vector <object> enemies;
    vector <object>::iterator it;
    
    // chua co code xoa sau khi ra khoi man hinh
    bool running = true;
    SDL_Event event;
    while (running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        
//           if (enemies.rect.y > 480*2) {enemies.rect.y=0;};
        
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

        
    
                
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    
    
    
    return 0;
}
