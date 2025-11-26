#ifndef INCLUDE_H
#define INCLUDE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include<iostream>
#include<fstream>
#include<string>

#include "mymap.h"
#include "Vector.h"
// #include "Texture.h"
// #include "game_map.h"
// #include "crop.h"
// #include "player.h"
// #include "Market.h"
// #include "TextBox.h"
// #include "AccountManager.h"
// #include "Login_Interface.h"
// #include "ChoosenSeed.h"
// #include "Setting.h"
// #include "shovel.h"
// #include "Water.h"
// #include "Tutorial.h"
// #include "Game.h"

using namespace std;

#define screen_width  1472
#define screen_height 896
#define tile_size 64
#define FPS 25
#define FRAME_DELAY (1000 / FPS)

//gia tri co ban
const int max_map_x = 64;
const int max_map_y = 64;
inline int root_map_x = 0;
inline int root_map_y = 0;

enum gameStage{
    LOGIN, PLAYING
};


#endif