#ifndef MARKET_H
#define MARKET_H

#include "Item.h"
#include "Inventory.h"
#include "player.h"
#include "mymap.h"
#include "Vector.h"

class Market{
    private:
        Vector<ItemType> itemForSale;
        mymap<ItemType, Texture> itemPositions;
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
        bool available_to_buy;
    public:
        Market(SDL_Renderer* renderer, TTF_Font *font);
        bool buyItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney);
        bool click(int x, int y, Inventory &playerInvenetory, Player &player, Mix_Chunk* sound1 = NULL, Mix_Chunk* sound2 = NULL);
        ItemType getItemAtPosition(int x, int y);
        bool checkUnlock(Player &player, ItemType item);
        void render(SDL_Renderer *renderer, TTF_Font* font, Player &player);
        void out();
        void set_buy(ItemType item, int quantity, int playerMoney);
};

#endif