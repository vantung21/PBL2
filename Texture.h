#ifndef TEXTURE_H
#define TEXTURE_H

#include "CommonFunction.h"

class Texture{
    protected:
        SDL_Texture* texture;
        SDL_Rect rect;
    public:
        Texture(int x = 0, int y = 0, int w = 50, int h = 30);
        ~Texture();
        bool Loadfromfile(SDL_Renderer *renderer, const string &path);
        void setRect(int x, int y, int w = -1, int h = -1);
        void render(SDL_Renderer* renderer);
        void SetColor(SDL_Renderer* renderer, SDL_Color c);
        void FillRect(SDL_Renderer* renderer, SDL_Color c); 
        void drawRect(SDL_Renderer* renderer, SDL_Color c);
        void write(SDL_Renderer *renderer, TTF_Font* font, string letter, SDL_Color c);       
        void free();
        SDL_Texture* getTexture(){ return texture;}
        SDL_Rect getRect(){ return rect;}
        bool checkClickTexture(int mouseX, int mouseY, Mix_Chunk* sound = NULL);
};

#endif