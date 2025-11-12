#ifndef TOOL_H
#define TOOL_H

#include "include.h"
#include "Texture.h"

class Tool{
    protected:
        bool hold;
    public:
        Tool(bool h);
        virtual ~Tool();
        void setHold(bool h);
        bool getHold();
        virtual void drop() = 0; 
        virtual void render(SDL_Renderer* renderer) = 0;
        virtual void setPos(int x, int y) = 0;
        virtual bool checkClick(int x, int y) = 0;
};

#endif