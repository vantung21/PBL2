#include "Inventory.h"

Inventory::Inventory(){
    selectedItem = ItemType(-1);
    inv_x = screen_width/8;
    inv_y = screen_height/8;
    inv_height = screen_height*6/8;
    inv_width = screen_width*6/8;
}
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

void Inventory :: render(SDL_Renderer *renderer, TTF_Font *font){
    
    // load anh nen
    Texture bgInventory;
    bgInventory.Loadfromfile(renderer, "image_game/BG_Inventory.png");
    bgInventory.setRect(inv_x,inv_y, inv_width, inv_height);
    bgInventory.render(renderer);

    // ve tieu de
    Texture titleInv;
    titleInv.write(renderer, font, "INVENTORY" , black);
    titleInv.setRect((inv_x + inv_width/2 - 64*3), (inv_y+32), 64*6, 64);
    titleInv.render(renderer);

    Texture line;
    line.setRect(inv_x + inv_width/2 - 64*3 - 32, inv_y + 106, 64*7, 4);
    line.FillRect(renderer, black);

    // ve cac items
    int item_x = inv_x + 10, item_y = inv_y + 126;
    for(auto &item : items){
        if(item.second > 0){

            //luu vi tri cac item trong inv
            itemPositions[item.first].setRect(item_x, item_y, 64, 64+20);

            // highlight o duoc chon
            if(selectedItem == item.first){
                itemPositions[item.first].FillRect(renderer, orange);
            }

            //ve item
            ItemDataBase::allItems[item.first].icon.setRect(item_x, item_y, 64, 64);
            ItemDataBase::allItems[item.first].icon.render(renderer);

            //ve so luong
            string s = to_string(item.second);
            int lenght = s.size();
            Texture quantityText;
            quantityText.setRect(item_x + (64-16*lenght)/2, item_y + 64, 16*lenght, 20);
            quantityText.FillRect(renderer, white);  
            quantityText.write(renderer, font, s, black);
            quantityText.render(renderer);

            //dieu chinh vi tri cho o tiep theo
            item_x += 64;
            if(item_x > inv_x + inv_width- 74){
                item_x = inv_x + 10;
                item_y += 94;
            }
        }
    }

    //ve khu vuc ban hang
    Texture areaSell;
    areaSell.setRect(inv_x, inv_y + inv_height - 140, inv_width, 140);
    areaSell.FillRect(renderer, gray);

    //
    if(selectedItem == ItemType(-1)){
        string select = "SELECTED: ";
        select += ItemDataBase::allItems[selectedItem].ItemName
                + "    Price: " 
                + to_string(ItemDataBase::allItems[selectedItem].sellPrice);
        
        Texture firstline;
        firstline.setRect(inv_x + 32, inv_y + inv_height - 120, select.size()*24, 40);
        firstline.write(renderer, font, select, black);
        firstline.render(renderer);

        //
        string quantity = "Quantity: ";
        Texture sl;
        sl.setRect(inv_x + 32, inv_y + inv_height - 60, quantity.size()*24, 40);
        sl.write(renderer, font, quantity, black);
        sl.render(renderer);
        //ve nut + -
        string plus10 = "+10";
        string plus1 = "+1";
        string tru10 = "-10";
        string tru1 = "-1";
        sl.setRect(inv_x + 32 + quantity.size()*24, inv_y + inv_height - 60, 3*24, 40);
        sl.FillRect(renderer, red);
        sl.write(renderer, font, tru10, black);
        sl.render(renderer);

        sl.setRect(inv_x + 32 + quantity.size()*24 + 4*24, inv_y + inv_height - 60, 3*24, 40);
        sl.FillRect(renderer, red);
        sl.write(renderer, font, tru1, black);
        sl.render(renderer);

        sl.setRect(inv_x + 32 + quantity.size()*24 +  8*24, inv_y + inv_height - 60, 3*24, 40);
        sl.FillRect(renderer, red);
        sl.write(renderer, font, plus1, black);
        sl.render(renderer);

        sl.setRect(inv_x + 32 + quantity.size()*24 + 12*24, inv_y + inv_height - 60, 3*24, 40);
        sl.FillRect(renderer, red);
        sl.write(renderer, font, plus10, black);
        sl.render(renderer);



    }
    
    


}