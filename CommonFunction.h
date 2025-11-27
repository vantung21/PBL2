#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include<iostream>
#include<fstream>
#include<string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "mymap.h"
#include "Vector.h"

using namespace std;

#define screen_width  1472
#define screen_height 896
#define tile_size 64
#define FPS 60
#define FRAME_DELAY (1000 / FPS)
#define white (SDL_Color){255, 255, 255, 255}
#define red (SDL_Color){255, 0 , 0, 255}
#define green (SDL_Color){0, 255, 0, 255}
#define blue (SDL_Color){0, 0, 255, 255}
#define orange (SDL_Color){200, 100, 0, 255}
#define black (SDL_Color){0, 0, 0, 255}
#define gray (SDL_Color){255, 255, 224, 225} 
#define yellow (SDL_Color){205, 205, 0, 255}
#define d_yellow (SDL_Color){175, 175, 0, 255}
#define l_blue (SDL_Color){0, 150, 155, 255}
#define d_red (SDL_Color){175, 30, 30, 255}
#define max_map_x 64
#define max_map_y 64


#endif