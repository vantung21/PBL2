#ifndef MARKET_H
#define MARKET_H

#include "Item.h"
#include "Inventory.h"

class Market{
    private:
        vector<ItemType> itemForSale;
        map<ItemType, Texture> itemPositions;
        ItemType selectedItem;
        int mrk_x;
        int mrk_y ;
        int mrk_height;
        int mrk_width;
        int slmua;
        Texture buy_, plus10_, plus1_, tru10_, tru1_;
    public:
        Market();
        bool buyItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney);
        bool click(int x, int y, Inventory &playerInvenetory, int &money);
        ItemType getItemAtPosition(int x, int y);
        void render(SDL_Renderer *renderer, TTF_Font* font);
};

#endif