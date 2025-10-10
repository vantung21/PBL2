#include "Item.h"

map<ItemType, ItemInfo> ItemDataBase::allItems;

void ItemDataBase::init(SDL_Renderer *renderer){
    static ItemInfo rice_seed;
    rice_seed.ItemName = "rice_seed";
    rice_seed.BuyPrice = 1;
    rice_seed.sellPrice = 0;
    rice_seed.icon.Loadfromfile(renderer, "image_game/rice_stage0.png");
    allItems[RICE_SEED] = rice_seed;

    static ItemInfo carrot_seed;;
    carrot_seed.ItemName = "carrot_seed";
    carrot_seed.BuyPrice = 2;
    carrot_seed.sellPrice = 0;
    carrot_seed.icon.Loadfromfile(renderer, "image_game/carrot_stage0.png");
    allItems[CARROT_SEED] = carrot_seed;

    static ItemInfo corn_seed;
    corn_seed.ItemName = "corn_seed";
    corn_seed.BuyPrice = 3;
    corn_seed.sellPrice = 0;
    corn_seed.icon.Loadfromfile(renderer, "image_game/corn.png");
    allItems[CORN_SEED] = corn_seed;

    static ItemInfo rice;
    rice.ItemName = "rice";
    rice.BuyPrice = 3;
    rice.sellPrice = 0;
    rice.icon.Loadfromfile(renderer, "image_game/rice.png");
    allItems[RICE] = rice;

    static ItemInfo carrot;
    carrot.ItemName = "carrot";
    carrot.BuyPrice = 3;
    carrot.sellPrice = 0;
    carrot.icon.Loadfromfile(renderer, "image_game/carrot.png");
    allItems[CARROT] = carrot;
    
    static ItemInfo corn;
    corn.ItemName = "corn";
    corn.BuyPrice = 3;
    corn.sellPrice = 0;
    corn.icon.Loadfromfile(renderer, "image_game/corn.png");
    allItems[CORN] = corn;
}