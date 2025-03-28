//
//  Button.c
//  Learning
//
//  Created by Huy Le's Macbook on 28/3/25.
//

#include "Button.h"


bool Button::handle_play_btn(SDL_Event event, SDL_Renderer* gRenderer, SDL_Texture* play_btn_texture, SDL_Rect play_btn_rect, SDL_Rect& render_rect){
    
    if (event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&mouse_rect.x, &mouse_rect.y);
    }
    if (SDL_HasIntersection(&mouse_rect, &play_btn_rect)){
        render_rect.x = render_rect.w;
        if (event.type == SDL_MOUSEBUTTONDOWN){
            return true;
        }
    }
    else{
        render_rect.x = 0;
    }
    return false;
}

