#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
enum playerStage{
    farm, inventory, market
};

class Player {
public:
    Player(const string name, int = 10);
    void updateStage(playerStage st);
    void render(SDL_Renderer *renderer);
    Inventory& getInventory();
    int &getMoney();
    playerStage getStage();
    string getname()const;

private:
    Inventory inventory;
    playerStage stage;
    string playername ;
    int money;
};

#endif  