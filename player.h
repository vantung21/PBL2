#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"

class Player {
public:
    Player(int = 10);
    void update();
    void render(SDL_Renderer *renderer);
    Inventory& getInventory();
    int &getMoney();

private:
    Inventory inventory;
    int money;
};

#endif  