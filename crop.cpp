#include "crop.h"

mymap<CropType, CropData> CropManager::allCropData;

void CropManager :: init(SDL_Renderer* renderer){
    //khoi tao du lieu cho rice
    static CropData riceData;
    riceData.name = "Rice";
    riceData.timePerStage = 12000; //ms
    riceData.totalStages = 4;
    riceData.exp = 1;
    riceData.stageTextures.resize(4);
    riceData.stageTextures[0].Loadfromfile(renderer, "image_game/rice_stage0.png");
    riceData.stageTextures[1].Loadfromfile(renderer, "image_game/rice_stage1.png");
    riceData.stageTextures[2].Loadfromfile(renderer, "image_game/rice_stage2.png");
    riceData.stageTextures[3].Loadfromfile(renderer, "image_game/rice_stage3.png");
    riceData.harvestedItems.push_back(RICE);
    //allCropData[RICE_cp] = riceData;
    allCropData.insert(RICE_cp, riceData);

    //carrot
    static CropData carrotData;
    carrotData.name = "Carrot";
    carrotData.timePerStage = 30000;
    carrotData.totalStages = 4;
    carrotData.exp = 2;
    carrotData.stageTextures.resize(4);
    carrotData.stageTextures[0].Loadfromfile(renderer, "image_game/carrot_stage0.png");
    carrotData.stageTextures[1].Loadfromfile(renderer, "image_game/carrot_stage1.png");
    carrotData.stageTextures[2].Loadfromfile(renderer, "image_game/carrot_stage2.png");
    carrotData.stageTextures[3].Loadfromfile(renderer, "image_game/carrot_stage3.png");
    carrotData.harvestedItems.push_back(CARROT);
    //allCropData[CARROT_cp] = carrotData;
    allCropData.insert(CARROT_cp, carrotData);

    //corn
    static CropData cornData;
    cornData.name = "Corn";
    cornData.timePerStage = 40000;
    cornData.totalStages = 4;
    cornData.exp = 4;
    cornData.stageTextures.resize(4);
    cornData.stageTextures[0].Loadfromfile(renderer, "image_game/corn_stage0.png");
    cornData.stageTextures[1].Loadfromfile(renderer, "image_game/corn_stage1.png");
    cornData.stageTextures[2].Loadfromfile(renderer, "image_game/corn_stage2.png");
    cornData.stageTextures[3].Loadfromfile(renderer, "image_game/corn_stage3.png");
    cornData.harvestedItems.push_back(CORN);
    //allCropData[CORN_cp] = cornData;
    allCropData.insert(CORN_cp, cornData);

    static CropData blueberryData;
    blueberryData.name = "Blueberry";
    blueberryData.timePerStage = 50000;
    blueberryData.totalStages = 4;
    blueberryData.exp = 4;
    blueberryData.stageTextures.resize(4);
    blueberryData.stageTextures[0].Loadfromfile(renderer, "image_game/blueberry_stage0.png");
    blueberryData.stageTextures[1].Loadfromfile(renderer, "image_game/blueberry_stage1.png");
    blueberryData.stageTextures[2].Loadfromfile(renderer, "image_game/blueberry_stage2.png");
    blueberryData.stageTextures[3].Loadfromfile(renderer, "image_game/blueberry_stage3.png");
    blueberryData.harvestedItems.push_back(BLUEBERRY);
    //allCropData[BLUEBERRY_cp] = blueberryData;
    allCropData.insert(BLUEBERRY_cp, blueberryData);

    static CropData cauliflowerData;
    cauliflowerData.name = "Cauliflower";
    cauliflowerData.timePerStage = 50000;
    cauliflowerData.totalStages = 4;
    cauliflowerData.exp = 5;
    cauliflowerData.stageTextures.resize(4);
    cauliflowerData.stageTextures[0].Loadfromfile(renderer, "image_game/cauliflower_stage0.png");
    cauliflowerData.stageTextures[1].Loadfromfile(renderer, "image_game/cauliflower_stage1.png");
    cauliflowerData.stageTextures[2].Loadfromfile(renderer, "image_game/cauliflower_stage2.png");
    cauliflowerData.stageTextures[3].Loadfromfile(renderer, "image_game/cauliflower_stage3.png");
    cauliflowerData.harvestedItems.push_back(CAULIFLOWER);
    //allCropData[CAULIFLOWER_cp] = cauliflowerData;
    allCropData.insert(CAULIFLOWER_cp, cauliflowerData);

    static CropData chiliData;
    chiliData.name = "Chili";
    chiliData.timePerStage = 35000;
    chiliData.totalStages = 4;
    chiliData.exp = 5;
    chiliData.stageTextures.resize(4);
    chiliData.stageTextures[0].Loadfromfile(renderer, "image_game/chili_stage0.png");
    chiliData.stageTextures[1].Loadfromfile(renderer, "image_game/chili_stage1.png");
    chiliData.stageTextures[2].Loadfromfile(renderer, "image_game/chili_stage2.png");
    chiliData.stageTextures[3].Loadfromfile(renderer, "image_game/chili_stage3.png");
    chiliData.harvestedItems.push_back(CHILI);
    //allCropData[CHILI_cp] = chiliData;
    allCropData.insert(CHILI_cp, chiliData);

    static CropData leekData;
    leekData.name = "Leek";
    leekData.timePerStage = 60000;
    leekData.totalStages = 4;
    leekData.exp = 5;
    leekData.stageTextures.resize(4);
    leekData.stageTextures[0].Loadfromfile(renderer, "image_game/leek_stage0.png");
    leekData.stageTextures[1].Loadfromfile(renderer, "image_game/leek_stage1.png");
    leekData.stageTextures[2].Loadfromfile(renderer, "image_game/leek_stage2.png");
    leekData.stageTextures[3].Loadfromfile(renderer, "image_game/leek_stage3.png");
    leekData.harvestedItems.push_back(LEEK);
    //allCropData[LEEK_cp] = leekData;
    allCropData.insert(LEEK_cp, leekData);

    static CropData potatoData;
    potatoData.name = "Potato";
    potatoData.timePerStage = 70000;
    potatoData.totalStages = 4;
    potatoData.exp = 6;
    potatoData.stageTextures.resize(4);
    potatoData.stageTextures[0].Loadfromfile(renderer, "image_game/potato_stage0.png");
    potatoData.stageTextures[1].Loadfromfile(renderer, "image_game/potato_stage1.png");
    potatoData.stageTextures[2].Loadfromfile(renderer, "image_game/potato_stage2.png");
    potatoData.stageTextures[3].Loadfromfile(renderer, "image_game/potato_stage3.png");
    potatoData.harvestedItems.push_back(POTATO);
    //allCropData[POTATO_cp] = potatoData;
    allCropData.insert(POTATO_cp, potatoData);

    static CropData pumpkinData;
    pumpkinData.name = "Pumpkin";
    pumpkinData.timePerStage = 85000;
    pumpkinData.totalStages = 4;
    pumpkinData.exp = 8;
    pumpkinData.stageTextures.resize(4);
    pumpkinData.stageTextures[0].Loadfromfile(renderer, "image_game/pumpkin_stage0.png");
    pumpkinData.stageTextures[1].Loadfromfile(renderer, "image_game/pumpkin_stage1.png");
    pumpkinData.stageTextures[2].Loadfromfile(renderer, "image_game/pumpkin_stage2.png");
    pumpkinData.stageTextures[3].Loadfromfile(renderer, "image_game/pumpkin_stage3.png");
    pumpkinData.harvestedItems.push_back(PUMPKIN);
    //allCropData[PUMPKIN_cp] = pumpkinData;
    allCropData.insert(PUMPKIN_cp, pumpkinData);

    static CropData strawberryData;
    strawberryData.name = "Strawberry";
    strawberryData.timePerStage = 100000;
    strawberryData.totalStages = 4;
    strawberryData.exp = 10;
    strawberryData.stageTextures.resize(4);
    strawberryData.stageTextures[0].Loadfromfile(renderer, "image_game/strawberry_stage0.png");
    strawberryData.stageTextures[1].Loadfromfile(renderer, "image_game/strawberry_stage1.png");
    strawberryData.stageTextures[2].Loadfromfile(renderer, "image_game/strawberry_stage2.png");
    strawberryData.stageTextures[3].Loadfromfile(renderer, "image_game/strawberry_stage3.png");
    strawberryData.harvestedItems.push_back(STRAWBERRY);
    //allCropData[STRAWBERRY_cp] = strawberryData;
    allCropData.insert(STRAWBERRY_cp, strawberryData);

    static CropData tomatoData;
    tomatoData.name = "Tomato";
    tomatoData.timePerStage = 120000;
    tomatoData.totalStages = 4;
    tomatoData.exp = 12;
    tomatoData.stageTextures.resize(4);
    tomatoData.stageTextures[0].Loadfromfile(renderer, "image_game/tomato_stage0.png");
    tomatoData.stageTextures[1].Loadfromfile(renderer, "image_game/tomato_stage1.png");
    tomatoData.stageTextures[2].Loadfromfile(renderer, "image_game/tomato_stage2.png");
    tomatoData.stageTextures[3].Loadfromfile(renderer, "image_game/tomato_stage3.png");
    tomatoData.harvestedItems.push_back(TOMATO);
    //allCropData[TOMATO_cp] = tomatoData;
    allCropData.insert(TOMATO_cp, tomatoData);

    static CropData watermelonData;
    watermelonData.name = "Watermelon";
    watermelonData.timePerStage = 150000;
    watermelonData.totalStages = 4;
    watermelonData.exp = 15;
    watermelonData.stageTextures.resize(4);
    watermelonData.stageTextures[0].Loadfromfile(renderer, "image_game/watermelon_stage0.png");
    watermelonData.stageTextures[1].Loadfromfile(renderer, "image_game/watermelon_stage1.png");
    watermelonData.stageTextures[2].Loadfromfile(renderer, "image_game/watermelon_stage2.png");
    watermelonData.stageTextures[3].Loadfromfile(renderer, "image_game/watermelon_stage3.png");
    watermelonData.harvestedItems.push_back(WATERMELON);
    //allCropData[WATERMELON_cp] = watermelonData;
    allCropData.insert(WATERMELON_cp, watermelonData);

    static CropData appleData;
    appleData.name = "Apple";
    appleData.timePerStage = 100000;
    appleData.totalStages = 7;
    appleData.exp = 40;
    appleData.stageTextures.resize(7);
    appleData.stageTextures[0].Loadfromfile(renderer, "image_game/Tao_0.png");
    appleData.stageTextures[1].Loadfromfile(renderer, "image_game/Tao_1.png");
    appleData.stageTextures[2].Loadfromfile(renderer, "image_game/Tao_2.png");
    appleData.stageTextures[3].Loadfromfile(renderer, "image_game/Tao_3.png");
    appleData.stageTextures[4].Loadfromfile(renderer, "image_game/Tao_4.png");
    appleData.stageTextures[5].Loadfromfile(renderer, "image_game/Tao_5.png");
    appleData.stageTextures[6].Loadfromfile(renderer, "image_game/Tao_6.png");
    appleData.harvestedItems.push_back(TAO);
    //allCropData[APPLE_cp] = appleData;
    allCropData.insert(APPLE_cp, appleData);
}

CropData&  CropManager :: getData(CropType type){
    return allCropData.at(type);
}

int Crop::count = 0;
Texture Crop::blingbling;
void Crop::loadBlingBling(SDL_Renderer* renderer){
    blingbling.Loadfromfile(renderer, "image_game/blingbling.png");
}
Crop :: Crop(CropType type, int x, int y): type(type){
    count++;
    growthStage = growthTimer = 0;
    position = {x, y, tile_size, tile_size};
}

void Crop::update(int deltaTime){
    growthTimer += deltaTime;
    const CropData& data = CropManager::getData(this->type);
    if(growthTimer >= data.timePerStage){
        growthTimer = growthTimer - data.timePerStage;
        growthStage++;
        if(growthStage >= data.totalStages) growthStage = data.totalStages-1;
    }
}
void Crop::render(SDL_Renderer* renderer){
    CropData& data = CropManager::getData(this->type);

    if(this->growthStage < data.totalStages){
        if(data.name == "Corn"){
            Texture& t =(Texture&)data.stageTextures[this->growthStage];
            t.setRect(position.x +root_map_x, position.y-tile_size + root_map_y, position.w, position.h*2);
            t.render(renderer);
            blingbling.setRect(position.x + tile_size/8 + root_map_x, position.y-tile_size + root_map_y, position.w*6/8, position.h*3/2);
        }
        else if(data.name == "Rice" || data.name == "Carrot" || data.name == "Pumpkin" || data.name == "Watermelon"){
            Texture& t =(Texture&)data.stageTextures[this->growthStage];
            t.setRect(position.x + root_map_x, position.y + root_map_y, position.w, position.h);
            t.render(renderer);
            blingbling.setRect(position.x + tile_size/8 + root_map_x, position.y + tile_size/8 + root_map_y, position.w*6/8, position.h*6/8);
        }
        else if(data.name == "Apple"){
            Texture& t =(Texture&)data.stageTextures[this->growthStage];
            t.setRect(position.x + root_map_x - tile_size, position.y + root_map_y - 3*tile_size, position.w*3, position.h*4);
            t.render(renderer);
            blingbling.setRect(position.x - tile_size + root_map_x, position.y - tile_size*7/3 + root_map_y, position.w*3, position.h*2);
        }
        else {
            Texture& t =(Texture&)data.stageTextures[this->growthStage];
            t.setRect(position.x + root_map_x, position.y + root_map_y - tile_size/5, position.w, position.h);
            t.render(renderer);
            blingbling.setRect(position.x + tile_size/8 + root_map_x, position.y + tile_size/8 + root_map_y, position.w*6/8, position.h*6/8);
        }    
    }
    if(this->isReadyToHarvest()){
        if(growthTimer%17 == 0){
            
            blingbling.render(renderer);
        }
    }
}

bool Crop::isReadyToHarvest() const{
    return this->growthStage == CropManager::getData(type).totalStages -1; 
}
CropType Crop::getType() const{
    return this->type;
}
int Crop::getTile_x() const{
    return this->position.x / tile_size;
}
int Crop::getTile_y() const{
    return this->position.y / tile_size;
}