#ifndef ITEM_H
#define ITEM_H

#include "include.h"
#include "Texture.h"
#include <map>

enum ItemType{
    //hat giong
    RICE_SEED,
    CARROT_SEED, 
    CORN_SEED,
    BLUEBERRY_SEED,
    CAULIFLOWER_SEED,
    CHILI_SEED,
    LEEK_SEED,
    POTATO_SEED,
    PUMPKIN_SEED,
    //RED_CABBAGE_SEED,
    STRAWBERRY_SEED,
    TOMATO_SEED,
    WATERMELON_SEED,
    
    //Tong seed
    COUNT_SEED,

    // SAN PHAM
    RICE,
    CARROT,
    CORN,
    BLUEBERRY,
    CAULIFLOWER,
    CHILI,
    LEEK,
    POTATO,
    PUMPKIN,
    //RED_CABBAGE,
    STRAWBERRY,
    TOMATO,
    WATERMELON,

    //tong
    COUNT
};

struct ItemInfo{
    string ItemName;
    Texture icon;
    int sellPrice;
    int buyPrice;
    int levelToUnlock;
};

class ItemDataBase{
    public:
        static map<ItemType, ItemInfo> allItems;
        static void init(SDL_Renderer *renderer);
};

#endif