#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory{
    private:
        mymap<ItemType, int > items;
        int soluongType;
        mymap<ItemType, Texture> itemPositions;
        ItemType selectedItem;
        int inv_x;
        int inv_y ;
        int inv_height;
        int inv_width;
        int slban;
        Texture sell_, plus10_, plus1_, tru10_, tru1_;
        Texture bgInventory, areaSell, line;
        Texture titleInv;
        string quantity, sell, tru1, tru10, plus1, plus10;
        
    public:
        Inventory(SDL_Renderer* renderer, TTF_Font* font);
        void addItem(ItemType item, int quantity);
        void removeItem(ItemType item, int quantity);
        int getQuantity(ItemType item) const ;
        int getcountType() const;
        bool saleItem(ItemType item, int quantity, int &playerMoney);
        bool click(int x, int y, int &money, Mix_Chunk* sound1 = NULL, Mix_Chunk* sound2 = NULL);
        ItemType getItemAtPosition(int x, int y);
        void render(SDL_Renderer *renderer, TTF_Font* font);
        void save(ofstream &saveFile);
        void clear();
        void out();
};

#endif