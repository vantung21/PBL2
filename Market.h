#ifndef MARKET_H
#define MARKET_H

#include "Item.h"
#include "Inventory.h"

class Market{
    private:
        vector<ItemType> itemForSale;
    public:
        Market(){};
        bool buyItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney);
        bool saleItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney);
        void render(SDL_Renderer *renderer);
};

#endif