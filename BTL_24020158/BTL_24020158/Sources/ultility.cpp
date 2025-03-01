//#include "ultility.h"
//#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>
//#include <iostream>
//SDL_Texture* loadBackground(const char* filePath, SDL_Renderer* renderer) {
//    SDL_Surface* tempSurface = IMG_Load(filePath);
//    if (!tempSurface) {
//        std::cerr << "Lỗi tải ảnh: " << IMG_GetError() << std::endl;
//        return nullptr;
//    }
//
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
//    SDL_FreeSurface(tempSurface);
//
//    if (!texture) {
//        std::cerr << "Lỗi tạo texture: " << SDL_GetError() << std::endl;
//    }
//
//    return texture;
//}
