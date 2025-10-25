#ifndef CHOOSENSEED_H
#define CHOOSENSEED_H

#include "Texture.h"
#include "include.h"
#include "player.h"
#include "crop.h"

class ChoosenSeed {
    private:
        vector<ItemType> availableItems; // luu cac item dang co
        Texture areaItemSelection;
        Texture openChoosenSeed;
        Texture arrowLeft, arrowRight;
        int itemOffset; // chi so bat dau hien thi
        int selectedIndex; // chi so cua item dc chon trong khung hien thi (0-4)
        bool isOpen; 

    public:
        ChoosenSeed(SDL_Renderer *renderer);
        bool checkclick(int x, int y);
        void xuLyClick(int x, int y, Player &tvt , CropType &current_cropTyppe);
        void render(SDL_Renderer *renderer, TTF_Font *font, Player &tvt, CropType &current_cropTyppe);
        vector<ItemType> getAvailableSeeds(Player &tvt); // duyet qua cac item de lay ra cac item dang co 
        int findItemIndex(const vector<ItemType>& items, const ItemType& item); // tim vi tri cua item trong vector availableItems

};

#endif