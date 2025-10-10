#include "Inventory.h"

void Inventory :: addItem(ItemType item, int quantity){
    items[item] += quantity;
}
void Inventory :: removeItem(ItemType item, int quantity){
    items[item] -= quantity;
    if(items[item] < 0 ) items[item] = 0;
}

int Inventory :: getQuantity(ItemType item) const{
    return items.at(item);
}

bool Inventory :: saleItem(ItemType item, int quantity, int &playerMoney){
    if(items[item] >= quantity){
        removeItem(item, quantity);
        playerMoney += ItemDataBase::allItems.at(item).BuyPrice*quantity;
        return true;
    }
    return false;
}

void Inventory :: render(SDL_Renderer *renderer){
    SDL_Rect wd_inventory= {64*5, 64*3, 64*15, 64*10};
    SDL_SetRenderDrawColor(renderer, 255, 150 , 0, 225);
    SDL_RenderFillRect(renderer, &wd_inventory);
    SDL_SetRenderDrawColor(renderer, 255, 200 , 200, 225);
    SDL_RenderDrawRect(renderer, &wd_inventory);
    int i = 64*5, j = 64*3;
    for(auto &x : items){
        if(x.second > 0){ 
            ItemDataBase::allItems[x.first].icon.setRect(i, j, 64,64);
            ItemDataBase::allItems[x.first].icon.render(renderer);
            i+= 64;
            if(i> 24*64){
                i = 64*5;
                j += 64;
            }
        }
    }
}