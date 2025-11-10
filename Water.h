#ifndef WATER_H
#define WATER_H

#include "include.h"
#include "Texture.h"

class Water{
    private:
        Texture water, watering, quantityTexture, bgW;
        int  w_x, w_y;
        bool hold;
        int quantity;
        bool isWatering;
        int loop;
        static const int recoveryTime = 30000;
        static const int maxQuatity = 50;
        int currTime;
    public:
        Water(SDL_Renderer* renderer, TTF_Font* font);
        void drop();
        void setHold(bool h);
        bool getHold();
        void render(SDL_Renderer* renderer);
        void setPos(int x, int y);
        bool checkClick(int x, int y);
        int getQuantity();
        void setQuantity(int sl);
        void Watering();
        void updateQuatity(SDL_Renderer* renderer, TTF_Font *font, int x);

};

#endif