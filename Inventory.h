#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory{
    private:
        map<ItemType, int > items;
        map<ItemType, Texture> itemPositions;
        ItemType selectedItem;
        int inv_x;
        int inv_y ;
        int inv_height;
        int inv_width;
        int slban;
        Texture sell_, plus10_, plus1_, tru10_, tru1_;
        
    public:
        Inventory();
        void addItem(ItemType item, int quantity);
        void removeItem(ItemType item, int quantity);
        int getQuantity(ItemType item) const ;
        bool saleItem(ItemType item, int quantity, int &playerMoney);
        bool click(int x, int y, int &money);
        ItemType getItemAtPosition(int x, int y);
        void render(SDL_Renderer *renderer, TTF_Font* font);
};

#endif