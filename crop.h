#ifndef CROP_H
#define CROP_H

#include "Texture.h"
#include <map>

enum CropType{
    RICE,
    CARROT,
    CORN
};

struct CropData{
    string name;
    int timePerStage; // thoi gian de qua 1 giai doan
    int totalStages; //tong so giai doan phat trien
    vector<Texture> stageTextures;  // load cac anh cua tung trang thai
};

class CropManager{
    private:
        static map< CropType, CropData> allCropData;
    public:
        static void init(SDL_Renderer* renderer);
        static const CropData& getData(CropType type);
};

class Crop{
    private:
        CropType type;
        int growthStage;
        int growthTimer;
        SDL_Rect position;  //vi tri va kich thuoc tren mang hinh
    public:
        Crop(CropType type, int , int );
        ~Crop(){;}
        void update(int deltaTime);
        void render(SDL_Renderer* renderer);
        
};

#endif