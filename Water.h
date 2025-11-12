#ifndef WATER_H
#define WATER_H

#include "Tool.h"

class Water : public Tool {
    private:
        Texture water, watering, quantityTexture, bgW;
        int  w_x, w_y;
        int quantity;
        bool isWatering;
        int loop;
        static const int recoveryTime = 30000;
        static const int maxQuantity = 50;
        int currTime;
    public:
        Water(SDL_Renderer* renderer, TTF_Font* font);
        void drop() override;
        void render(SDL_Renderer* renderer) override;
        void setPos(int x, int y) override;
        bool checkClick(int x, int y) override;
        int getQuantity();
        void setQuantity(int sl);
        void Watering();
        void updateQuatity(SDL_Renderer* renderer, TTF_Font *font, int x);
};

#endif