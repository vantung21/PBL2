#ifndef ITEM_H
#define ITEM_H

#include "include.h"
#include "Texture.h"
#include <map>

enum ItemType{
    //hat giong
    RICE_SEED, CARROT_SEED, CORN_SEED,

    // SAN PHAM
    RICE, CARROT, CORN


};

struct ItemInfo{
    string ItemName;
    Texture icon;
    int sellPrice;
    int BuyPrice;
};

class ItemDataBase{
    public:
        static map<ItemType, ItemInfo> allItems;
        static void init(SDL_Renderer *renderer);
};

#endif