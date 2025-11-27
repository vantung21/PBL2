#include "Texture.h"

Texture :: Texture(int x, int y, int w, int h): rect({x,y,w,h}){
    texture = NULL;
    //rect = {0, 0, 0, 0};
}
Texture :: ~Texture(){
    free();
}

bool Texture :: Loadfromfile(SDL_Renderer *renderer, const string &path){
    free();
    SDL_Surface* loadsurface = IMG_Load(path.c_str());
    if(!loadsurface){
        cout << "Loi khong load duoc anh " << path << " !\n";
        return false;
    }
    //SDL_SetColorKey(loadsurface, SDL_TRUE, SDL_MapRGB(loadsurface->format, 0, 0, 0)); // lam mau nen den trong suot
    texture = SDL_CreateTextureFromSurface(renderer, loadsurface);
    if(!texture){
        cout << "Loi khong tao duoc texture tu " << path << " !\n";
        SDL_FreeSurface(loadsurface);
        return false;
    }
    rect.w = loadsurface->w;
    rect.h = loadsurface->h;
    SDL_FreeSurface(loadsurface);
    return true;
}

void Texture :: setRect(int x, int y, int w, int h){
    rect = {x, y, (w == -1)?rect.w:w, (h == -1)?rect.h : h};
}
void Texture::SetColor(SDL_Renderer* renderer, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void Texture :: render(SDL_Renderer* renderer){
    if(texture){

        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void Texture::FillRect(SDL_Renderer* renderer, SDL_Color c){
    SetColor(renderer, c);
    SDL_RenderFillRect(renderer, &rect);
}

void Texture::drawRect(SDL_Renderer* renderer, SDL_Color c){
    SetColor(renderer, c);
    SDL_RenderDrawRect(renderer, &rect);
}

void Texture :: free(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
        rect = {0, 0, 0, 0};
    }
}

void Texture::write(SDL_Renderer *renderer, TTF_Font* font, string letter, SDL_Color c){
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, letter.c_str(), c);
    this->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

bool Texture::checkClickTexture(int mouseX, int mouseY, Mix_Chunk* sound){
    if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h){
            if(sound){
                Mix_PlayChannel(-1, sound, 0);
            }
            return true;
    }
    return false;
}