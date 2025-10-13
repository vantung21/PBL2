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
    bgInventory.Loadfromfile(renderer, "image_game/BG_Inventory2.png");
    bgInventory.setRect(inv_x,inv_y, inv_width, inv_height);
    bgInventory.render(renderer);
    bgInventory.drawRect(renderer, black);

    // ve tieu de
    Texture titleInv;
    titleInv.write(renderer, font, "INVENTORY" , black);
    titleInv.setRect((inv_x + inv_width/2 - 64*3), (inv_y+32), 64*6, 64);
    titleInv.render(renderer);

    Texture line;
    line.setRect(inv_x + inv_width/2 - 64*3 - 32, inv_y + 106, 64*7, 4);
    line.FillRect(renderer, black);

    //Tungf depj trai
    // ve cac items
    int item_x = inv_x + 10, item_y = inv_y + 126;
    for(auto &item : items){
        if(item.second > 0){

            //luu vi tri cac item trong inv
            itemPositions[item.first].setRect(item_x, item_y, 100, 100+30);

            // highlight o duoc chon
            if(selectedItem == item.first){
                itemPositions[item.first].FillRect(renderer, orange);
            }

            //ve item
            ItemDataBase::allItems[item.first].icon.setRect(item_x, item_y, 100, 100);
            ItemDataBase::allItems[item.first].icon.render(renderer);

            //ve so luong
            string s = to_string(item.second);
            int lenght = s.size();
            Texture quantityText;
            quantityText.setRect(item_x + (100-14*lenght)/2, item_y + 100, 14*lenght, 30);
            quantityText.FillRect(renderer, white);
            quantityText.drawRect(renderer, black);  
            quantityText.write(renderer, font, s, black);
            quantityText.render(renderer);

            //dieu chinh vi tri cho o tiep theo
            item_x += 100;
            if(item_x > inv_x + inv_width- 110){
                item_x = inv_x + 10;
                item_y += 140;
            }
        }
    }

    //ve khu vuc ban hang
    Texture areaSell;
    areaSell.setRect(inv_x, inv_y + inv_height - 140, inv_width, 140);
    areaSell.FillRect(renderer, gray);
    areaSell.drawRect(renderer, black);

    //
    if(selectedItem == ItemType(-1)){
        string select = "SELECTED: ";
        select += ItemDataBase::allItems[selectedItem].ItemName
                + "    Price: " 
                + to_string(ItemDataBase::allItems[selectedItem].sellPrice);
        
        Texture firstline;
        firstline.setRect(inv_x + 32, inv_y + inv_height - 120, select.size()*16, 40);
        firstline.write(renderer, font, select, black);
        firstline.render(renderer);

        //
        string quantity = "Quantity: ";
        Texture sl;
        sl.setRect(inv_x + 32, inv_y + inv_height - 60, quantity.size()*16, 40);
        sl.write(renderer, font, quantity, black);
        sl.render(renderer);
        //ve nut + -
        string plus10 = "+10";
        string plus1 = "+1";
        string tru10 = "-10";
        string tru1 = "-1";
        sl.setRect(inv_x + 32 + quantity.size()*16, inv_y + inv_height - 60, 3*16, 40);
        sl.FillRect(renderer, red);
        sl.drawRect(renderer, black);
        sl.write(renderer, font, tru10, black);
        sl.render(renderer);

        sl.setRect(inv_x + 32 + quantity.size()*16 + 4*16, inv_y + inv_height - 60, 3*16, 40);
        sl.FillRect(renderer, red);
        sl.drawRect(renderer, black);
        sl.write(renderer, font, tru1, black);
        sl.render(renderer);

        sl.setRect(inv_x + 32 + quantity.size()*16 +  14*16, inv_y + inv_height - 60, 3*16, 40);
        sl.FillRect(renderer, red);
        sl.drawRect(renderer, black);
        sl.write(renderer, font, plus1, black);
        sl.render(renderer);

        sl.setRect(inv_x + 32 + quantity.size()*16 + 18*16, inv_y + inv_height - 60, 3*16, 40);
        sl.FillRect(renderer, red);
        sl.drawRect(renderer, black);
        sl.write(renderer, font, plus10, black);
        sl.render(renderer);

        slban = 1;
        sl.setRect(inv_x + 32 + quantity.size()*16 + 7*16 + (7-to_string(slban).size())*16/2, inv_y + inv_height - 60, to_string(slban).size()*16, 35);
        sl.write(renderer, font, to_string(slban), blue);
        sl.render(renderer);
        sl.setRect(inv_x + 32 + quantity.size()*16 + 7*16 + 8, inv_y + inv_height - 60 + 38, 6*16, 2);
        sl.FillRect(renderer, black);

        int t = slban*ItemDataBase::allItems[selectedItem].sellPrice;
        string tong = "Total Sales: ";
        tong += to_string(t);
        sl.setRect(inv_x + inv_width - 20*16, inv_y + inv_height - 120, tong.size()*16, 40);
        sl.write(renderer, font, tong, black);
        sl.render(renderer);

        string sell = " SELL ";
        sl.setRect(inv_x + inv_width - 13*16, inv_y + inv_height - 70, 7*16, 60);
        sl.FillRect(renderer, green);
        sl.drawRect(renderer, black);
        sl.write(renderer, font, sell, black);
        sl.render(renderer);
    }
    
    // anh truong dap trai


}