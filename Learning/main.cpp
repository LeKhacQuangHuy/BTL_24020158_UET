//  Created by Huy Le's Macbook on 28/2/25.
#include "GameBase.h"
#include "GameUltis.h"
using namespace std;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Texture *gTexture = nullptr;


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
                
                
                
                //Clear screen
                SDL_RenderClear( gRenderer );
                
                //Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                
                //Update screen
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
        
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            success = false;
        }
    }
    
    return success;
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool loadmedia(){
    bool success = true;
    //Load PNG texture
    gTexture = loadTexture( "src/background.png" );
    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    return success;
    
}
void close()
{
    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
