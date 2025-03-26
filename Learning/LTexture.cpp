//
//  LTexture.c
//  Learning
//
//  Created by Huy Le's Macbook on 6/3/25.
//

#include "LTexture.h"
SDL_Texture* LTexture::load_pic_from_file(std::string FILE_PATH, SDL_Renderer* gRenderer){
    SDL_Texture* lTexture = nullptr;
    SDL_Surface* lSurface = IMG_Load(FILE_PATH.c_str());
    if (lSurface == nullptr){
        std::cout << "Failed to load picture" << IMG_GetError();
    }
    else
    {
        lTexture = SDL_CreateTextureFromSurface(gRenderer, lSurface);
        if (lTexture == nullptr){
            std::cout << "Failed to create picture texture from surface";
        }
    }
    SDL_FreeSurface(lSurface);
    return lTexture;
}

SDL_Texture* LTexture::load_text(std::string TEXT_PATH, std::string TEXT2LOAD, SDL_Renderer* gRenderer){
    SDL_Texture* lTexture = nullptr;
    TTF_Font* font = TTF_OpenFont(TEXT_PATH.c_str(), 35); // Chọn font chữ và kích thước
    if (!font) {
        std::cerr << "Không thể tải font: " << TTF_GetError() << std::endl;
    }
    SDL_Color textColor = {255, 255, 255}; // Màu chữ: trắng
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, TEXT2LOAD.c_str(), textColor);
    if (textSurface == NULL){
        std::cout << TTF_GetError();
    }
    lTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return lTexture;
}

SDL_Rect LTexture::create_rect(SDL_Texture* texture, int x, int y){
    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = { x, y, textWidth, textHeight };
    return textRect;
}
