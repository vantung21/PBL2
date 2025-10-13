#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory{
    private:
        map<ItemType, int > items;
    public:
        Inventory();
        void addItem(ItemType item, int quantity);
        void removeItem(ItemType item, int quantity);
        int getQuantity(ItemType item) const ;
        bool saleItem(ItemType item, int quantity, int &playerMoney);
        void render(SDL_Renderer *renderer);
};


#endif