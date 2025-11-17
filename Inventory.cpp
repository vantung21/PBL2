#include "Inventory.h"

Inventory::Inventory(SDL_Renderer* renderer, TTF_Font* font){
    soluongType = 0;
    selectedItem = ItemType(-1);
    inv_x = screen_width/8;
    inv_y = screen_height/8;
    inv_height = screen_height*6/8;
    inv_width = screen_width*6/8;
    slban = 1;

    bgInventory.Loadfromfile(renderer, "image_game/BG_Inventory2.png");
    bgInventory.setRect(inv_x,inv_y, inv_width, inv_height);

    titleInv.write(renderer, font, "INVENTORY" , black);
    titleInv.setRect((inv_x + inv_width/2 - 64*3), (inv_y+32), 64*6, 64);

    line.setRect(inv_x + inv_width/2 - 64*3 - 32, inv_y + 106, 64*7, 4);

    areaSell.setRect(inv_x, inv_y + inv_height - 140, inv_width, 140);

    quantity = "Quantity: ";
    plus10 = "+10";
    plus1 = "+1";
    tru10 = "-10";
    tru1 = "-1";
    tru10_.write(renderer, font, tru10, black);
    tru10_.setRect(inv_x + 32 + quantity.size()*16, inv_y + inv_height - 60, 3*16, 40);
    tru1_.write(renderer, font, tru1, black);
    tru1_.setRect(inv_x + 32 + quantity.size()*16 + 4*16, inv_y + inv_height - 60, 3*16, 40);
    plus1_.write(renderer, font, plus1, black);
    plus1_.setRect(inv_x + 32 + quantity.size()*16 +  14*16, inv_y + inv_height - 60, 3*16, 40);
    plus10_.write(renderer, font, plus10, black);
    plus10_.setRect(inv_x + 32 + quantity.size()*16 + 18*16, inv_y + inv_height - 60, 3*16, 40);

    sell = " SELL ";
    sell_.write(renderer, font, sell, black);
    sell_.setRect(inv_x + inv_width - 13*16, inv_y + inv_height - 70, 7*16, 60);


}
void Inventory :: addItem(ItemType item, int quantity){
    if((items.find(item) == items.end()) || items[item] == 0) this->soluongType++;
    items[item] += quantity;
}
void Inventory :: removeItem(ItemType item, int quantity){
    items[item] -= quantity;
    if(items[item] <= 0 ){
        items[item] = 0;
        this->soluongType--;
    } 
    
}

int Inventory :: getQuantity(ItemType item) const{
    if(items.find(item) == items.end()) return -1;
    return items.at(item);
}

int Inventory::getcountType()const{
    return soluongType;
}

bool Inventory :: saleItem(ItemType item, int quantity, int &playerMoney){
    if(items[item] >= quantity){
        removeItem(item, quantity);
        playerMoney += ItemDataBase::allItems.at(item).sellPrice*quantity;
        return true;
    }
    return false;
}

void Inventory :: render(SDL_Renderer *renderer, TTF_Font *font){
    
    // load anh nen
    bgInventory.render(renderer);
    bgInventory.drawRect(renderer, black);

    // ve tieu de
    titleInv.render(renderer);

    line.FillRect(renderer, black);

    // ve cac items
    int item_x = inv_x + 50, item_y = inv_y + 120;
    itemPositions.clear();
    for(auto &item : items){
        if(item.second > 0){

            //luu vi tri cac item trong inv
            itemPositions[item.first].setRect(item_x, item_y, 100, 100+30);

            // highlight o duoc chon
            if(selectedItem == item.first){
                itemPositions[item.first].FillRect(renderer, yellow);
                itemPositions[item.first].drawRect(renderer, black);
            }

            //ve item
            ItemDataBase::allItems[item.first].icon.setRect(item_x, item_y, 100, 100);
            ItemDataBase::allItems[item.first].icon.render(renderer);

            //ve so luong
            string s = to_string(item.second);
            int lenght = s.size();
            Texture quantityText;
            quantityText.write(renderer, font, s, black);
            quantityText.setRect(item_x + (100-14*lenght)/2, item_y + 100, 14*lenght, 30);
            quantityText.FillRect(renderer, white);
            quantityText.drawRect(renderer, black);  
            quantityText.render(renderer);

            //dieu chinh vi tri cho o tiep theo
            item_x += 100;
            if(item_x > inv_x + inv_width- 110){
                item_x = inv_x + 50;
                item_y += 140;
            }
        }
    }

    //ve khu vuc ban hang
    areaSell.FillRect(renderer, gray);
    areaSell.drawRect(renderer, black);

    //
    if(selectedItem != ItemType(-1)){
        string select = "Selected: ";
        select += ItemDataBase::allItems[selectedItem].ItemName
                + "    Price: " 
                + to_string(ItemDataBase::allItems[selectedItem].sellPrice);
        
        Texture firstline;
        firstline.write(renderer, font, select, black);
        firstline.setRect(inv_x + 32, inv_y + inv_height - 120, select.size()*16, 40);
        firstline.render(renderer);

        //
        
        Texture sl;
        sl.write(renderer, font, quantity, black);
        sl.setRect(inv_x + 32, inv_y + inv_height - 60, quantity.size()*16, 40);
        sl.render(renderer);
        //ve nut + -
        tru10_.FillRect(renderer, red);
        tru10_.drawRect(renderer, black);
        tru10_.render(renderer);

        tru1_.FillRect(renderer, red);
        tru1_.drawRect(renderer, black);
        tru1_.render(renderer);

        plus1_.FillRect(renderer, red);
        plus1_.drawRect(renderer, black);
        plus1_.render(renderer);
    
        plus10_.FillRect(renderer, red);
        plus10_.drawRect(renderer, black);
        plus10_.render(renderer);

        sl.write(renderer, font, to_string(slban), blue);
        sl.setRect(inv_x + 32 + quantity.size()*16 + 7*16 + (7-to_string(slban).size())*16/2, inv_y + inv_height - 60, to_string(slban).size()*16, 35);
        sl.render(renderer);
        sl.setRect(inv_x + 32 + quantity.size()*16 + 7*16 + 8, inv_y + inv_height - 60 + 38, 6*16, 2);
        sl.FillRect(renderer, black);

        int t = slban*ItemDataBase::allItems[selectedItem].sellPrice;
        string tong = "Total Sales: ";
        tong += to_string(t);
        sl.write(renderer, font, tong, black);
        sl.setRect(inv_x + inv_width - 20*16, inv_y + inv_height - 120, tong.size()*16, 40);
        sl.render(renderer);

        sell_.FillRect(renderer, green);
        sell_.drawRect(renderer, black);
        sell_.render(renderer);
    }
}

ItemType Inventory::getItemAtPosition(int x, int y){
    for( auto& pair : itemPositions){
        if(x >= pair.second.getRect().x && x <= pair.second.getRect().x + pair.second.getRect().w &&
           y >= pair.second.getRect().y && y <= pair.second.getRect().y + pair.second.getRect().h)
            return pair.first;
    }
    return ItemType(-1);
}

bool Inventory::click(int x, int y, int &money, Mix_Chunk* sound1, Mix_Chunk* sound2){
    bool run = true;
    ItemType clickedItem = getItemAtPosition(x, y);
    if(clickedItem != ItemType(-1)){
        this->selectedItem = clickedItem;
    }
    else if(this->selectedItem != ItemType(-1)){
        if(sell_.checkClickTexture(x, y, sound1)){
            saleItem(this->selectedItem, slban, money);
            this->selectedItem = ItemType(-1);
            slban = 1;
        }
        else if(tru10_.checkClickTexture(x, y, sound2)){
            slban -= 10;
            if(slban <= 0) slban = 1;
        }
        else if(tru1_.checkClickTexture(x, y, sound2)){
            slban -= 1;
            if(slban <= 0) slban = 1;
        }
        else if(plus10_.checkClickTexture(x, y, sound2)){
            slban += 10;
            if(slban >= items[selectedItem]) slban = items[selectedItem];
        }
        else if(plus1_.checkClickTexture(x, y, sound2)){
            slban += 1;
            if(slban >= items[selectedItem]) slban = items[selectedItem];
        }
        else if(x <= inv_x || x >= inv_x + inv_width || y <= inv_y || y >= inv_y + inv_height){
            Mix_PlayChannel(-1, sound2, 0);
            out();
            run = false;
        }
        else {
            out();
        }
    }
    else if(x <= inv_x || x >= inv_x + inv_width || y <= inv_y || y >= inv_y + inv_height){
        Mix_PlayChannel(-1, sound2, 0);
        out();
        run = false;
    }
    return run;
}

void Inventory::save(ofstream &saveFile){
    saveFile << soluongType << endl;
    for(auto &item : items){
        if(item.second > 0)
            saveFile << item.first << " " << item.second << endl;
    }
}
void Inventory::clear(){
    items.clear();
    soluongType = 0;
    selectedItem = ItemType(-1);
    slban = 1;
}
void Inventory::out(){
    this->selectedItem = ItemType(-1);
    this->slban = 1;
}