#ifndef SHOVEL_H
#define SHOVEL_H

#include "Tool.h"

class  Shovel : public Tool {
    private:
        Texture shovel, bgS;
        int  s_x, s_y;
    public:
        Shovel(SDL_Renderer* renderer);
        void drop() override;
        void render(SDL_Renderer* renderer) override;
        void setPos(int x, int y) override;
        bool checkClick(int x, int y) override;

};


#endif