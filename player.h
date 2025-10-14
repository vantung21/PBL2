#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
enum playerStage{
    farm, inventory, market
};

class Player {
public:
    Player(int = 10);
    void updateStage(playerStage st);
    void render(SDL_Renderer *renderer);
    Inventory& getInventory();
    int &getMoney();
    playerStage getStage();

private:
    Inventory inventory;
    playerStage stage;
    int money;
};

#endif  