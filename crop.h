#ifndef CROP_H
#define CROP_H

#include "Texture.h"
#include "mymap.h"
#include "Item.h"

enum CropType{
    RICE_cp,
    CARROT_cp,
    CORN_cp,
    BLUEBERRY_cp,
    CAULIFLOWER_cp,
    CHILI_cp,
    LEEK_cp,
    POTATO_cp,
    PUMPKIN_cp,
    STRAWBERRY_cp,
    TOMATO_cp,
    WATERMELON_cp,
    APPLE_cp
};

struct CropData{
    string name;
    int timePerStage; // thoi gian de qua 1 giai doan
    int totalStages; //tong so giai doan phat trien
    int exp; // kinh nghiem 
    Vector<ItemType> harvestedItems;
    Vector<Texture> stageTextures;  // load cac anh cua tung trang thai
};

class CropManager{
    private:
        static mymap< CropType, CropData> allCropData;
    public:
        static void init(SDL_Renderer* renderer);
        static CropData& getData(CropType type);
};

class Crop{
    private:
        CropType type;
        int growthStage;
        int growthTimer;
        SDL_Rect position;  //vi tri va kich thuoc tren mang hinh
    public:
        static int count;
        static Texture blingbling;
        static void loadBlingBling(SDL_Renderer* renderer);
        Crop(CropType type, int = 0 , int = 0 );
        ~Crop(){count--;}
        void update(int deltaTime);
        void render(SDL_Renderer* renderer);
        bool isReadyToHarvest() const;
        CropType getType() const;
        int getTile_x() const;
        int getTile_y() const;
        int& getGrowthStage() { return growthStage; }    
        int& getGrowthTimer() { return growthTimer; }   
};

#endif