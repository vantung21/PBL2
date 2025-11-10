#ifndef MARKET_H
#define MARKET_H

#include "Item.h"
#include "Inventory.h"
#include "player.h"

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
        Texture buy_, plus10_, plus1_, tru10_, tru1_, lock;
        Texture bgInventory, titleInv, line, areaSbuy;
        string plus10;
        string plus1;
        string tru10;
        string tru1;
        string quantity;
        string buy;
    public:
        Market(SDL_Renderer* renderer, TTF_Font *font);
        bool buyItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney);
        bool click(int x, int y, Inventory &playerInvenetory, Player &player);
        ItemType getItemAtPosition(int x, int y);
        bool checkUnlook(Player &player, ItemType item);
        void render(SDL_Renderer *renderer, TTF_Font* font, Player &player);
};

#endif