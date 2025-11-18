#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "include.h"
#include "Texture.h"

class Tutorial{
    private:
        int t_x, t_y, t_w, t_h;
        static const int number_crop = 13;
        static const int number_guide = 5;
        Texture BG, cropTx, guideTx;
        Texture crop[number_crop];
        Texture guide[number_guide];
        Texture arrow_right, arrow_left;
        bool is_crop;
        int cur_crop, cur_guide;
    public:
        Tutorial(SDL_Renderer* renderer, TTF_Font* font);
        void render(SDL_Renderer* renderer);
        bool click(int mouseX, int mouseY, Mix_Chunk* sound = NULL);
        void out();

};

#endif