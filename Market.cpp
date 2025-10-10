#include "Market.h"

bool Market :: buyItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney){
    int price = ItemDataBase::allItems.at(item).BuyPrice*quantity;
    if(playerMoney >= price){
        playerInvenetory.addItem(item, quantity);
        playerMoney -= price;
        return true;
    }
    return false;
}

void Market :: render(SDL_Renderer *renderer){
    SDL_Rect wd_inventory= {64*5, 64*3, 64*15, 64*10};
    SDL_SetRenderDrawColor(renderer, 255, 150 , 0, 225);
    SDL_RenderFillRect(renderer, &wd_inventory);
    SDL_SetRenderDrawColor(renderer, 255, 200 , 200, 225);
    SDL_RenderDrawRect(renderer, &wd_inventory);
    
}