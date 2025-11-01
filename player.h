#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "include.h"

enum playerStage{
    farm, inventory, market, setting
};

class Player {
public:
    Player(SDL_Renderer* renderer = nullptr, TTF_Font* font = nullptr, int ID = 100000, const string name = "player", int = 10);
    void updateStage(playerStage st);
    void render(SDL_Renderer *renderer);
    Inventory& getInventory();
    int &getMoney();
    playerStage getStage();
    string& getname();
    int& getID() { return player_ID; }

private:
    Inventory inventory;
    playerStage stage;
    string playername ;
    int money;
    int player_ID;
    int exp, level;
    Texture nameTexture, levelTexture, expTexture, moneyTexture;  
};

#endif  