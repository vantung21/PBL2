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

    static ItemInfo blueberry_seed;
    blueberry_seed.ItemName = "blueberry_seed";
    blueberry_seed.buyPrice = 15;
    blueberry_seed.sellPrice = 4;
    blueberry_seed.icon.Loadfromfile(renderer, "image_game/blueberry_seed.png");
    allItems[BLUEBERRY_SEED] = blueberry_seed;

    static ItemInfo cauliflower_seed;
    cauliflower_seed.ItemName = "cauliflower_seed";
    cauliflower_seed.buyPrice = 12;
    cauliflower_seed.sellPrice = 4;
    cauliflower_seed.icon.Loadfromfile(renderer, "image_game/cauliflower_seed.png");
    allItems[CAULIFLOWER_SEED] = cauliflower_seed;

    static ItemInfo chili_seed;
    chili_seed.ItemName = "chili_seed";
    chili_seed.buyPrice = 10;
    chili_seed.sellPrice = 4;
    chili_seed.icon.Loadfromfile(renderer, "image_game/chili_seed.png");
    allItems[CHILI_SEED] = chili_seed;

    static ItemInfo leek_seed;
    leek_seed.ItemName = "leek_seed";
    leek_seed.buyPrice = 9;
    leek_seed.sellPrice = 4;
    leek_seed.icon.Loadfromfile(renderer, "image_game/leek_seed.png");
    allItems[LEEK_SEED] = leek_seed;

    static ItemInfo potato_seed;
    potato_seed.ItemName = "potato_seed";
    potato_seed.buyPrice = 8;
    potato_seed.sellPrice = 4;
    potato_seed.icon.Loadfromfile(renderer, "image_game/potato_seed.png");
    allItems[POTATO_SEED] = potato_seed;

    static ItemInfo pumpkin_seed;
    pumpkin_seed.ItemName = "pumpkin_seed";
    pumpkin_seed.buyPrice = 11;
    pumpkin_seed.sellPrice = 4;
    pumpkin_seed.icon.Loadfromfile(renderer, "image_game/pumpkin_seed.png");
    allItems[PUMPKIN_SEED] = pumpkin_seed;

    // static ItemInfo red_cabbage_seed;
    // red_cabbage_seed.ItemName = "red_cabbage_seed";
    // red_cabbage_seed.buyPrice = 10;
    // red_cabbage_seed.sellPrice = 4;
    // red_cabbage_seed.icon.Loadfromfile(renderer, "image_game/red_cabbage_seed.png");
    // allItems[RED_CABBAGE_SEED] = red_cabbage_seed;

    static ItemInfo strawberry_seed;
    strawberry_seed.ItemName = "strawberry_seed";
    strawberry_seed.buyPrice = 15;
    strawberry_seed.sellPrice = 4;
    strawberry_seed.icon.Loadfromfile(renderer, "image_game/strawberry_seed.png");
    allItems[STRAWBERRY_SEED] = strawberry_seed;

    static ItemInfo tomato_seed;
    tomato_seed.ItemName = "tomato_seed";
    tomato_seed.buyPrice = 9;
    tomato_seed.sellPrice = 4;
    tomato_seed.icon.Loadfromfile(renderer, "image_game/tomato_seed.png");
    allItems[TOMATO_SEED] = tomato_seed;

    static ItemInfo watermelon_seed;
    watermelon_seed.ItemName = "watermelon_seed";
    watermelon_seed.buyPrice = 15;
    watermelon_seed.sellPrice = 4;
    watermelon_seed.icon.Loadfromfile(renderer, "image_game/watermelon_seed.png");
    allItems[WATERMELON_SEED] = watermelon_seed;

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

    static ItemInfo blueberry;
    blueberry.ItemName = "blueberry";
    blueberry.buyPrice = 17;
    blueberry.sellPrice = 12;
    blueberry.icon.Loadfromfile(renderer, "image_game/blueberry.png");
    allItems[BLUEBERRY] = blueberry;

    static ItemInfo cauliflower;
    cauliflower.ItemName = "cauliflower";
    cauliflower.buyPrice = 12;
    cauliflower.sellPrice = 9;
    cauliflower.icon.Loadfromfile(renderer, "image_game/cauliflower.png");
    allItems[CAULIFLOWER] = cauliflower;

    static ItemInfo chili;
    chili.ItemName = "chili";
    chili.buyPrice = 12;
    chili.sellPrice = 8;
    chili.icon.Loadfromfile(renderer, "image_game/chili.png");
    allItems[CHILI] = chili;

    static ItemInfo leek;
    leek.ItemName = "leek";
    leek.buyPrice = 10;
    leek.sellPrice = 7;
    leek.icon.Loadfromfile(renderer, "image_game/leek.png");
    allItems[LEEK] = leek;

    static ItemInfo potato;
    potato.ItemName = "potato";
    potato.buyPrice = 8;
    potato.sellPrice = 8;
    potato.icon.Loadfromfile(renderer, "image_game/potato.png");
    allItems[POTATO] = potato;

    static ItemInfo pumpkin;
    pumpkin.ItemName = "pumpkin";
    pumpkin.buyPrice = 12;
    pumpkin.sellPrice = 9;
    pumpkin.icon.Loadfromfile(renderer, "image_game/pumpkin.png");
    allItems[PUMPKIN] = pumpkin;

    // static ItemInfo red_cabbage;
    // red_cabbage.ItemName = "red_cabbage";
    // red_cabbage.buyPrice = 10;
    // red_cabbage.sellPrice = 4;
    // red_cabbage.icon.Loadfromfile(renderer, "image_game/red_cabbage.png");
    // allItems[RED_CABBAGE] = red_cabbage;

    static ItemInfo strawberry;
    strawberry.ItemName = "strawberry";
    strawberry.buyPrice = 18;
    strawberry.sellPrice = 12;
    strawberry.icon.Loadfromfile(renderer, "image_game/strawberry.png");
    allItems[STRAWBERRY] = strawberry;

    static ItemInfo tomato;
    tomato.ItemName = "tomato";
    tomato.buyPrice = 10;
    tomato.sellPrice = 8;
    tomato.icon.Loadfromfile(renderer, "image_game/tomato.png");
    allItems[TOMATO] = tomato;

    static ItemInfo watermelon;
    watermelon.ItemName = "watermelon";
    watermelon.buyPrice = 20;
    watermelon.sellPrice = 12;
    watermelon.icon.Loadfromfile(renderer, "image_game/watermelon.png");
    allItems[WATERMELON] = watermelon;
}