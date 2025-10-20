#include "Item.h"

map<ItemType, ItemInfo> ItemDataBase::allItems;

void ItemDataBase::init(SDL_Renderer *renderer){
    static ItemInfo rice_seed;
    rice_seed.ItemName = "rice_seed";
    rice_seed.buyPrice = 2;
    rice_seed.sellPrice = 1;
    rice_seed.icon.Loadfromfile(renderer, "image_game/rice_stage0.png");
    allItems[RICE_SEED] = rice_seed;

    static ItemInfo carrot_seed;;
    carrot_seed.ItemName = "carrot_seed";
    carrot_seed.buyPrice = 4;
    carrot_seed.sellPrice = 2;
    carrot_seed.icon.Loadfromfile(renderer, "image_game/carrot_stage0.png");
    allItems[CARROT_SEED] = carrot_seed;

    static ItemInfo corn_seed;
    corn_seed.ItemName = "corn_seed";
    corn_seed.buyPrice = 10;
    corn_seed.sellPrice = 4;
    corn_seed.icon.Loadfromfile(renderer, "image_game/corn_seed.png");
    allItems[CORN_SEED] = corn_seed;

    static ItemInfo rice;
    rice.ItemName = "rice";
    rice.buyPrice = 4;
    rice.sellPrice = 3;
    rice.icon.Loadfromfile(renderer, "image_game/rice.png");
    allItems[RICE] = rice;

    static ItemInfo carrot;
    carrot.ItemName = "carrot";
    carrot.buyPrice = 10;
    carrot.sellPrice = 7;
    carrot.icon.Loadfromfile(renderer, "image_game/carrot.png");
    allItems[CARROT] = carrot;
    
    static ItemInfo corn;
    corn.ItemName = "corn";
    corn.buyPrice = 13;
    corn.sellPrice = 9;
    corn.icon.Loadfromfile(renderer, "image_game/corn.png");
    allItems[CORN] = corn;
}