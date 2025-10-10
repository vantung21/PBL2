#include "crop.h"

map<CropType, CropData> CropManager::allCropData;

void CropManager :: init(SDL_Renderer* renderer){
    //khoi tao du lieu cho rice
    static CropData riceData;
    riceData.name = "Rice";
    riceData.timePerStage = 20;
    riceData.totalStages = 4;
    riceData.stageTextures.resize(4);
    riceData.stageTextures[0].Loadfromfile(renderer, "image_game/rice_stage0.png");
    riceData.stageTextures[1].Loadfromfile(renderer, "image_game/rice_stage1.png");
    riceData.stageTextures[2].Loadfromfile(renderer, "image_game/rice_stage2.png");
    riceData.stageTextures[3].Loadfromfile(renderer, "image_game/rice_stage3.png");
    allCropData[RICE] = riceData;

    //carrot
    static CropData carrotData;
    carrotData.name = "Carrot";
    carrotData.timePerStage = 20;
    carrotData.totalStages = 4;
    carrotData.stageTextures.resize(4);
    carrotData.stageTextures[0].Loadfromfile(renderer, "image_game/carrot_stage0.png");
    carrotData.stageTextures[1].Loadfromfile(renderer, "image_game/carrot_stage1.png");
    carrotData.stageTextures[2].Loadfromfile(renderer, "image_game/carrot_stage2.png");
    carrotData.stageTextures[3].Loadfromfile(renderer, "image_game/carrot_stage3.png");
    allCropData[CARROT] = carrotData;

    //corn
    static CropData cornData;
    cornData.name = "Corn";
    cornData.timePerStage = 20;
    cornData.totalStages = 4;
    cornData.stageTextures.resize(4);
    cornData.stageTextures[0].Loadfromfile(renderer, "image_game/corn_stage0.png");
    cornData.stageTextures[1].Loadfromfile(renderer, "image_game/corn_stage1.png");
    cornData.stageTextures[2].Loadfromfile(renderer, "image_game/corn_stage2.png");
    cornData.stageTextures[3].Loadfromfile(renderer, "image_game/corn_stage3.png");
    allCropData[CORN] = cornData;
}

const CropData&  CropManager :: getData(CropType type){
    return allCropData.at(type);
}


Crop :: Crop(CropType type, int x, int y): type(type){
    growthStage = growthTimer = 0;
    position = {x, y, tile_size, tile_size};
}

void Crop::update(int deltaTime){
    growthTimer += deltaTime;
    const CropData& data = CropManager::getData(this->type);
    if(growthTimer >= data.timePerStage){
        growthTimer = 0;
        growthStage++;
        if(growthStage >= 4) growthStage = 3;
    }
}
void Crop::render(SDL_Renderer* renderer){
    const CropData& data = CropManager::getData(this->type);
    if(data.name == "Corn"){
        Texture& t =(Texture&)data.stageTextures[this->growthStage];
        t.setRect(position.x +root_map_x, position.y-tile_size + root_map_y, position.w, position.h*2);
        t.render(renderer);
        return;
    }

    if(this->growthStage < data.totalStages){
        Texture& t =(Texture&)data.stageTextures[this->growthStage];
        t.setRect(position.x + root_map_x, position.y + root_map_y, position.w, position.h);
        t.render(renderer);
    }
}