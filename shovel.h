#ifndef SHOVEL_H
#define SHOVEL_H

#include "include.h"
#include "Texture.h"

class  Shovel{
    private:
        Texture shovel, bgS;
        int  s_x, s_y;
        bool hold;
    public:
        Shovel(SDL_Renderer* renderer);
        void drop();
        void setHold(bool h);
        bool getHold();
        void render(SDL_Renderer* renderer);
        void setPos(int x, int y);
        bool checkClick(int x, int y);

};


#endif