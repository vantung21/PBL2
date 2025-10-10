#ifndef INCLUDE_H
#define INCLUDE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

#define screen_width 1600
#define screen_height 960
#define tile_size 32

//gia tri co ban
const int max_map_x = 64;
const int max_map_y = 64;
inline int root_map_x = 0;
inline int root_map_y = 0;

#endif