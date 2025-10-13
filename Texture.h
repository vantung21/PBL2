#ifndef TEXTURE_H
#define TEXTURE_H

#include "include.h"

extern SDL_Color white;
extern SDL_Color red ;
extern SDL_Color green;
extern SDL_Color blue ;
extern SDL_Color orange ;
extern SDL_Color black;
extern SDL_Color gray;

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
        void SetColor(SDL_Renderer* renderer, SDL_Color c);
        void FillRect(SDL_Renderer* renderer, SDL_Color c); 
        void write(SDL_Renderer *renderer, TTF_Font* font, string letter, SDL_Color c);       
        void free();
        SDL_Texture* getTexture(){ return texture;}
        SDL_Rect getRect(){ return rect;}
};

#endif