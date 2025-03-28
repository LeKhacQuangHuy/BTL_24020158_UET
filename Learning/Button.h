//
//  Button.h
//  Learning
//
//  Created by Huy Le's Macbook on 28/3/25.
//

#ifndef Button_h
#define Button_h

#include <stdio.h>
#include "GameBase.h"
#include "GameUltis.h"
#include "GameObject.h"
#include "LTexture.h"
class Button{
public:
    bool handle_play_btn(SDL_Event event, SDL_Renderer* gRenderer, SDL_Texture* play_btn_texture, SDL_Rect play_btn_rect, SDL_Rect& render_rect);
    
private:
    SDL_Rect mouse_rect = {0, 0, 10, 10};
};


#endif /* Button_h */
