//  Created by Huy Le's Macbook on 28/2/25.
#include "GameBase.h"
#include "GameUltis.h"
#include "LTexture.h"
#include "GamePlayer.h"
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


const Uint8 * keystate = SDL_GetKeyboardState(nullptr);

object player;
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



    // Khởi tạo SDL và SDL_mixer
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mix Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Tải nhạc (MP3, WAV, OGG, v.v.)
    Mix_Music* music = Mix_LoadMUS("sound/bkgr_audio.wav");
    if (!music) {
        std::cerr << "Failed to load music! Mix Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Phát nhạc (-1 để lặp vô hạn, 0 để phát 1 lần)
    Mix_PlayMusic(music, -1);

    std::cout << "Press Enter to stop music..." << std::endl;
//    std::cin.get(); // Đợi người dùng nhấn Enter



            
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
                draw_high_score();
                //Render yourscore
                draw_your_score();
                //Render player
                player.update();
//                SDL_RenderCopy(gRenderer, player.objectTexture, NULL, &player.objectRect);
                SDL_RenderCopyEx(gRenderer, player.objectTexture, NULL, &player.objectRect, 0, NULL, player.flip);
                
                
                
                SDL_RenderPresent(gRenderer);
                
            
                SDL_Delay(20);
                
            }
                
   
            
            Mix_FreeMusic(music);
            Mix_CloseAudio();
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
    SDL_Surface* icon = IMG_Load(ICON_PATH);
    SDL_SetWindowIcon(gWindow, icon);
    SDL_FreeSurface(icon);
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
    background_texture = gLoader.load_pic_from_file(GameBackground_PATH, gRenderer);
    if(background_texture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    highscore_texture = gLoader.load_text(Font_PATH, "High score: ", gRenderer);
    if (highscore_texture == NULL){
        cout << "Failed to load high score texture" << endl;
        success = false;
    }
    yourscore_texture = gLoader.load_text("font/pixel_font.ttf", "Your score: ", gRenderer);
    if (yourscore_texture == NULL){
        cout << "Failed to load your score texture" << endl;
        success = false;
    }
    
    player.objectTexture = gLoader.load_pic_from_file(Player_PATH, gRenderer);
    player.x = PLAYER_INIT_X;
    player.y = PLAYER_INIT_Y;
    player.objectRect = gLoader.create_rect(player.objectTexture, PLAYER_INIT_X, PLAYER_INIT_Y);
    if (player.objectTexture == NULL){
        cout << "Failed to load your player texture" << IMG_GetError() << endl;
        success = false;
    }
    return success;
    
}
void close()
{
    //audio

    
    //Texture
    SDL_DestroyTexture(highscore_texture);
    SDL_DestroyTexture(yourscore_texture);
    SDL_DestroyTexture(player.objectTexture);
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
void draw_high_score(){
    highscore_rect = gLoader.create_rect(highscore_texture, HIGH_SCORE_X, HIGH_SCORE_Y);
    SDL_RenderCopy(gRenderer, highscore_texture, NULL, &highscore_rect);
}
void draw_your_score(){
    yourscore_rect = gLoader.create_rect(yourscore_texture, HIGH_SCORE_X, HIGH_SCORE_Y + HIGH_YOUR_SCORE_SPACE );
    SDL_RenderCopy(gRenderer, yourscore_texture, NULL, &yourscore_rect);
}
void draw_player(){

}
