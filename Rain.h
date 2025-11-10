#ifndef RAIN_H
#define RAIN_H

#include "include.h"
#include "Texture.h"

 

class Rain{
    private:
        Texture rainTexture[3][3][3];
        static const int timeEvent = 120000;
        int loop, stage, currTime ;
        bool isRaining;
    public:
        Rain(SDL_Renderer* renderer);
        void execute(SDL_Renderer* renderer);
        bool getIsRaining();
        void setIsRaining(bool raining);
        void updateTime(int time);
        void resetCurrTime();
};

#endif