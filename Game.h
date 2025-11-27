#ifndef GAME_H
#define GAME_H

#include "CommonFunction.h"
#include "game_map.h"
#include "crop.h"
#include "player.h"
#include "Market.h"
#include "TextBox.h"
#include "AccountManager.h"
#include "Login_Interface.h"
#include "ChoosenSeed.h"
#include "Setting.h"
#include "shovel.h"
#include "Water.h"
#include "Tutorial.h"
#include "Rain.h"


enum gameStage{
    LOGIN, PLAYING
};

class Game {
private:

    // music + sfx
    Mix_Music* music_game;
    Mix_Chunk *buttonSound, *trongcaySound, *thuhoachSound, *leveupSound;
    Mix_Chunk *openDoorSound, *tingTingSound, *shovelSound, *wateringSound;

    // game objects
    Player player_;
    GameMap gameMap_;
    Market market_;
    Setting setting_;
    Tutorial tutorial_;
    Shovel shovel_;
    Water water_;
    Rain rain_; 

    ChoosenSeed choosen_seed;
    Login_Interface loginUI;
    AccountManager accountManager;

    Texture icon_inv, icon_market, icon_setting, icon_tutorial, house;

    gameStage current_gameStage;  // LOGIN / PLAYING
    CropType current_cropType;

    bool running;
    bool windowActive;
    int root_map_x;
    int root_map_y;

public:
    Game();
    ~Game();
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static TTF_Font* font;

    void run();
    static bool initSDL();

private:
    void loadResources();
    void loadIcons();

    void saveGame();
    void loadGame();

    void handleLoginEvents(SDL_Event& e);
    void handlePlayingEvents(SDL_Event& e);

    void update();
    void render();

    void quitSDL();
};  

#endif
