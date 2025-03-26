//  Created by Huy Le's Macbook on 28/2/25.
#include "GameBase.h"
#include "GameUltis.h"
#include "LTexture.h"
#include "GameObject.h"
//using namespace std;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
//TTF_Font* gFont = nullptr;

SDL_Texture* background_texture;
SDL_Texture* highscore_texture;
SDL_Texture* yourscore_texture;
SDL_Texture* yourscore_num_texture;
SDL_Texture* bonus_score_texture;
SDL_Texture* high_score_num_texture;

SDL_Rect highscore_rect;
SDL_Rect yourscore_rect;
SDL_Rect yourscore_num_rect;
SDL_Rect bonus_score_rect;
SDL_Rect high_score_num_rect;

LTexture gLoader;

Mix_Music* gMusic = nullptr;
Mix_Chunk* gKeyboard = nullptr;
const Uint8 * keystate = SDL_GetKeyboardState(nullptr);

object player;
object example_white_enemies;
object example_yellow_enemies;
object example_boost_enemies;

enemies white_ene;
enemies yellow_ene;
enemies boost_ene;

int your_score = 0;
int high_score = 0;
int MAX_SCORE = 0;

Uint32 handle_bonus_delay_time;
using namespace std;

int main(int argc, char* argv[]){
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
                Mix_PlayMusic(gMusic, -1);
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
                    
                    draw_your_score(your_score);
                    
                    //Render player
                    player.update();
                    SDL_RenderCopyEx(gRenderer, player.objectTexture, NULL, &player.objectRect, 0, NULL, player.flip);
                    //Render white enemies
                    if (getRandomNum(0, 30) == 0){
                        white_ene.gen_new_enemies(2, example_white_enemies, gRenderer, WHITE_ENE_PATH);
                    }
                    if (white_ene.handle_white_enemies(player) == 1){
                        your_score += 1;
                    }
                    
                    white_ene.render(example_white_enemies.objectTexture, gRenderer, WHITE_ENE_PATH);
                    //Render boost enemies
                    if (getRandomNum(0, 100) == 0){
                        boost_ene.gen_new_enemies(3, example_boost_enemies, gRenderer, BOOST_ENE_PATH);
                    }
                    if (boost_ene.handle_boost_enemies(player) == 1){
                        your_score += 5;
                        handle_bonus_delay_time = SDL_GetTicks();
                    }
                    if (handle_delay_action(handle_bonus_delay_time, 3) == true){
                        show_bonus_score(player.objectRect.x, player.objectRect.y);
                    }
                    boost_ene.render(example_boost_enemies.objectTexture, gRenderer, BOOST_ENE_PATH);
                    
                    //Render yellow enemies
                    if (getRandomNum(0, 100) == 0){
                        yellow_ene.gen_new_enemies(2, example_yellow_enemies, gRenderer, YELLOW_ENE_PATH);
                    }
                    if (yellow_ene.handle_yellow_enemies(player) == 0){
                        yellow_ene.render(example_white_enemies.objectTexture, gRenderer, YELLOW_ENE_PATH);
                        SDL_RenderPresent(gRenderer);
                        SDL_Delay(20);
                    }
                    else {
                        show_lose_screen(running);
                        white_ene.reset();
                        yellow_ene.reset();
                        player.objectRect.x = PLAYER_INIT_X;
                        player.objectRect.y = PLAYER_INIT_Y;
                        high_score_num_texture = gLoader.load_text(Font_PATH, high_score_num(your_score, MAX_SCORE), gRenderer);
                        high_score_num_rect = gLoader.create_rect(high_score_num_texture, high_score_num_rect.x, high_score_num_rect.y);
                        your_score = 0;
                    }
                }
            }
        }
    close();
        return 0;
    
}
bool init(){
    bool success = true;
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        std::cout << "SDL Init Error!" << SDL_GetError();
        success = false;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        cout << "AUDIO INIT ERROR!" << SDL_GetError();
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
    //Audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
    if (!gMusic){
        cout << "Failed to load background music" << Mix_GetError() << endl;
        success = false;
    }
//    gKeyboard = Mix_LoadWAV("sound/mouse_click.wav");
//    player.load_audio(gKeyboard);
    //High score
    highscore_texture = gLoader.load_text(Font_PATH, "High score: ", gRenderer);
    highscore_rect = gLoader.create_rect(highscore_texture, HIGH_SCORE_X, HIGH_SCORE_Y);
    cout << high_score_num(your_score, MAX_SCORE) << endl;
    high_score_num_texture = gLoader.load_text(Font_PATH, high_score_num(your_score, MAX_SCORE), gRenderer);
    high_score_num_rect = gLoader.create_rect(high_score_num_texture, HIGH_SCORE_X + highscore_rect.w + 3, HIGH_SCORE_Y);
    if (highscore_texture == NULL){
        cout << "Failed to load high score texture" << endl;
        success = false;
    }
    //Your score
    yourscore_texture = gLoader.load_text(Font_PATH, "Your score: ", gRenderer);
    if (yourscore_texture == NULL){
        cout << "Failed to load your score texture" << endl;
        success = false;
    }
    yourscore_num_texture = gLoader.load_text("font/pixel_font.ttf", to_string(your_score) , gRenderer);
    yourscore_rect = gLoader.create_rect(yourscore_texture, HIGH_SCORE_X, HIGH_SCORE_Y + HIGH_YOUR_SCORE_SPACE );
    if (yourscore_texture == NULL){
        cout << "Failed to load your score texture" << endl;
        success = false;
    }
    
    //Player
    player.objectTexture = gLoader.load_pic_from_file(Player_PATH, gRenderer);
    player.x = PLAYER_INIT_X;
    player.y = PLAYER_INIT_Y;
    player.objectRect = gLoader.create_rect(player.objectTexture, PLAYER_INIT_X, PLAYER_INIT_Y);
    if (player.objectTexture == NULL){
        cout << "Failed to load your player texture" << IMG_GetError() << endl;
        success = false;
    }
    //White enemies
    example_white_enemies.objectTexture = gLoader.load_pic_from_file(WHITE_ENE_PATH, gRenderer);
    if (example_white_enemies.objectTexture == NULL){
        cout << "Failed to load your white enemies texture" << IMG_GetError() << endl;
        success = false;
    }
    //Yellow enemies
    example_yellow_enemies.objectTexture = gLoader.load_pic_from_file(YELLOW_ENE_PATH, gRenderer);
    if (example_yellow_enemies.objectTexture == NULL){
        cout << "Failed to load your yellow enemies texture" << IMG_GetError() << endl;
        success = false;
    }
    //Boost enemies
    example_boost_enemies.objectTexture = gLoader.load_pic_from_file(BOOST_ENE_PATH, gRenderer);
    if (example_boost_enemies.objectTexture == NULL){
        cout << "Failed to load your boost enemies texture" << IMG_GetError() << endl;
        success = false;
    }
    //Bonus
    bonus_score_texture = gLoader.load_text(Font_PATH, "+5", gRenderer);
    if (bonus_score_texture == NULL){
        cout << "Failed to load your boost enemies texture" << IMG_GetError() << endl;
        success = false;
    }
    return success;
    
}
void close()
{
    //audio
    
    Mix_FreeMusic(gMusic);
//    Mix_FreeChunk(gKeyboard);
    Mix_CloseAudio();
    //Texture
    SDL_DestroyTexture(highscore_texture);
    SDL_DestroyTexture(yourscore_texture);
    SDL_DestroyTexture(player.objectTexture);
    SDL_DestroyTexture(yourscore_num_texture);
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL  subsystems
    IMG_Quit();
    SDL_Quit();
}
void draw_high_score(){
    SDL_RenderCopy(gRenderer, highscore_texture, NULL, &highscore_rect);
    SDL_RenderCopy(gRenderer, high_score_num_texture, NULL, &high_score_num_rect);
}
void draw_your_score(int score){
    
    SDL_DestroyTexture(yourscore_num_texture);
    yourscore_num_texture = nullptr;

        

    SDL_RenderCopy(gRenderer, yourscore_texture, NULL, &yourscore_rect);
   
    yourscore_num_texture = gLoader.load_text(Font_PATH, to_string(your_score), gRenderer);
    yourscore_num_rect = gLoader.create_rect(yourscore_num_texture,HIGH_SCORE_X + yourscore_rect.w + 0.5 , HIGH_SCORE_Y + HIGH_YOUR_SCORE_SPACE);
    SDL_RenderCopy(gRenderer, yourscore_num_texture, NULL, &yourscore_num_rect);
}
void show_lose_screen(bool &play_Again){
    SDL_Texture* lose_screeen = gLoader.load_text(Font_PATH, "DO YOU WANT TO PLAY AGAIN ?", gRenderer);
    SDL_Rect lose_rect = gLoader.create_rect(lose_screeen, MAX_SCREEN_WEIGHT/2 - 300, MAX_SCREEN_HEIGHT/2);
    SDL_Event e;
    
    bool running = true;
    while (running){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                play_Again = false;
                SDL_DestroyTexture(lose_screeen);
                running = false;
            }
            if (e.type == SDL_KEYDOWN){
                play_Again = true;
                SDL_DestroyTexture(lose_screeen);
                running = false;
                
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0,0,0,0);
        SDL_RenderClear(gRenderer);
        
        SDL_RenderCopy(gRenderer, lose_screeen, NULL, &lose_rect);
        
        SDL_RenderPresent(gRenderer);
        SDL_Delay(20);
    }
}
void show_bonus_score(int x, int y){
    bonus_score_rect = gLoader.create_rect(bonus_score_texture, x, y);
    SDL_RenderCopy(gRenderer, bonus_score_texture, NULL, &bonus_score_rect);
    SDL_Delay(10);
}
