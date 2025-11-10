#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "include.h"

enum playerStage{
    farm, inventory, market, setting, shovel, watering
};

class Player {
public:
    Player(SDL_Renderer* renderer = NULL, TTF_Font* font = NULL, int ID = 100000, const string name = "player", int = 10);
    void updateStage(playerStage st);
    void updateExp(SDL_Renderer *renderer, TTF_Font* font, int x);
    void update_nameText(SDL_Renderer *renderer, TTF_Font* font);
    void update_moneyTexture(SDL_Renderer *renderer, TTF_Font* font);
    void render(SDL_Renderer *renderer);
    Inventory& getInventory();
    int &getMoney();
    playerStage getStage();
    string& getname();
    int& getID() { return player_ID; }
    int& getLevel(){return level;}
    int& getExp(){return exp;}
    void clear();

private:
    Inventory inventory;
    playerStage stage;
    string playername ;
    int money;
    int player_ID;
    int exp, level;
    Texture nameTexture,nameText , levelTexture, expTexture, currExp, moneyTexture;  
};

#endif  