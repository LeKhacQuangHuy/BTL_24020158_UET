//  Created by Huy Le's Macbook on 28/2/25.
#include "GameBase.h"
#include "GameUltis.h"
#include "LTexture.h"
using namespace std;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
//TTF_Font* gFont = nullptr;

SDL_Texture* background_texture;
SDL_Texture* highscore_texture;
SDL_Texture* yourscore_texture;

SDL_Rect highscore_rect;
SDL_Rect yourscore_rect;

LTexture gLoader;


int main(){
    if (!init()){
        cout << "Can't init" << SDL_GetError();
    }
    else
    {
        if (!loadmedia()){
            cout << "Can't load media" << SDL_GetError();
        }
        
        else{
            
            
            SDL_Event event;
            bool running = true;
            while (running){
                while (SDL_PollEvent(&event)){
                    if (event.type == SDL_QUIT){
                        running = false;
                    }
                }
                
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
                SDL_RenderClear(gRenderer);
                
                
                
                SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
                
                //Render highscore
                highscore_rect = gLoader.create_text_rect(highscore_texture, HIGH_SCORE_X, HIGH_SCORE_Y);
                SDL_RenderCopy(gRenderer, highscore_texture, NULL, &highscore_rect);
                
                //Render yourscore
                yourscore_rect = gLoader.create_text_rect(yourscore_texture, HIGH_SCORE_X, HIGH_SCORE_Y + HIGH_YOUR_SCORE_SPACE );
                
                SDL_RenderCopy(gRenderer, yourscore_texture, NULL, &yourscore_rect);
                SDL_RenderPresent(gRenderer);
                
            
                SDL_Delay(30);
                
            }
                
   
            
            
            close();
        }
    }
    return 0;
}
bool init(){
    bool success = true;
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        std::cout << "SDL Init Error!" << SDL_GetError();
        success = false;
    }
    else
    {
        int img_flag = IMG_INIT_PNG;
        if (!(IMG_Init(img_flag) & img_flag)){
            std::cout << "SDL IMG Init Error!" << SDL_GetError();
            success = false;
        }
    }
    gWindow = SDL_CreateWindow(GameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAX_SCREEN_WEIGHT, MAX_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        cout << "Can't create window" << SDL_GetError();
        success = false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, 0, 0);
    if (gRenderer == nullptr)
    {
        cout << "Can't create renderer" << SDL_GetError();
        success = false;
    } else
        {
        //Initialize renderer color
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        
            if (TTF_Init() < 0){
                cout << "Could not initalize text" << TTF_GetError();
                success = false;
            }
            
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
                }
        }

    return success;
}




bool loadmedia(){
    bool success = true;
    //Load PNG texture
    background_texture = gLoader.load_pic_from_file("src/background.png", gRenderer);
    if(background_texture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    highscore_texture = gLoader.load_text("font/pixel_font.ttf", "High score: ", gRenderer);
    if (highscore_texture == NULL){
        cout << "Failed to load high score texture";
        success = false;
    }
    yourscore_texture = gLoader.load_text("font/pixel_font.ttf", "Your score: ", gRenderer);
    if (yourscore_texture == NULL){
        cout << "Failed to load your score texture";
        success = false;
    }
    return success;
    
}
void close()
{
    //Free loaded image
//    SDL_DestroyTexture( gTexture );
//    gTexture = NULL;
    gLoader.Free();
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
