#ifndef INCLUDE_H
#define INCLUDE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

#define screen_width 1088
#define screen_height 768
#define tile_size 64

//gia tri co ban
const int max_map_x = 64;
const int max_map_y = 64;
inline int root_map_x = 0;
inline int root_map_y = 0;

#endif