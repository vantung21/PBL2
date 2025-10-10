#ifndef TEXTURE_H
#define TEXTURE_H

#include "include.h"

class Texture{
    protected:
        SDL_Texture* texture;
        SDL_Rect rect;
    public:
        Texture();
        ~Texture();
        bool Loadfromfile(SDL_Renderer *renderer, const string &path);
        void setRect(int x, int y, int w = -1, int h = -1);
        void render(SDL_Renderer* renderer);        
        void free();
        SDL_Texture* getTexture(){ return texture;}
        SDL_Rect getRect(){ return rect;}
};

#endif