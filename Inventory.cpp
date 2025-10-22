#include "Inventory.h"

Inventory::Inventory(){
    soluongType = 0;
    selectedItem = ItemType(-1);
    inv_x = screen_width/8;
    inv_y = screen_height/8;
    inv_height = screen_height*6/8;
    inv_width = screen_width*6/8;
    slban = 1;
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

    // ve cac items
    int item_x = inv_x + 10, item_y = inv_y + 126;
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
    if(selectedItem != ItemType(-1)){
        string select = "SELECTED: ";
        select += ItemDataBase::allItems[selectedItem].ItemName
                + "    Price: " 
                + to_string(ItemDataBase::allItems[selectedItem].sellPrice);
        
        Texture firstline;
        firstline.write(renderer, font, select, black);
        firstline.setRect(inv_x + 32, inv_y + inv_height - 120, select.size()*16, 40);
        firstline.render(renderer);

        //
        string quantity = "Quantity: ";
        Texture sl;
        sl.write(renderer, font, quantity, black);
        sl.setRect(inv_x + 32, inv_y + inv_height - 60, quantity.size()*16, 40);
        sl.render(renderer);
        //ve nut + -
        string plus10 = "+10";
        string plus1 = "+1";
        string tru10 = "-10";
        string tru1 = "-1";
        tru10_.write(renderer, font, tru10, black);
        tru10_.setRect(inv_x + 32 + quantity.size()*16, inv_y + inv_height - 60, 3*16, 40);
        tru10_.FillRect(renderer, red);
        tru10_.drawRect(renderer, black);
        tru10_.render(renderer);

        tru1_.write(renderer, font, tru1, black);
        tru1_.setRect(inv_x + 32 + quantity.size()*16 + 4*16, inv_y + inv_height - 60, 3*16, 40);
        tru1_.FillRect(renderer, red);
        tru1_.drawRect(renderer, black);
        tru1_.render(renderer);

        plus1_.write(renderer, font, plus1, black);
        plus1_.setRect(inv_x + 32 + quantity.size()*16 +  14*16, inv_y + inv_height - 60, 3*16, 40);
        plus1_.FillRect(renderer, red);
        plus1_.drawRect(renderer, black);
        plus1_.render(renderer);
    
        plus10_.write(renderer, font, plus10, black);
        plus10_.setRect(inv_x + 32 + quantity.size()*16 + 18*16, inv_y + inv_height - 60, 3*16, 40);
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

        string sell = " SELL ";
        sell_.write(renderer, font, sell, black);
        sell_.setRect(inv_x + inv_width - 13*16, inv_y + inv_height - 70, 7*16, 60);
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

bool Inventory::click(int x, int y, int &money){
    bool run = true;
    ItemType clickedItem = getItemAtPosition(x, y);
    if(clickedItem != ItemType(-1)){
        this->selectedItem = clickedItem;
    }
    else{
        if(x >= sell_.getRect().x && x <= sell_.getRect().x + sell_.getRect().w &&
            y >= sell_.getRect().y && y <= sell_.getRect().y + sell_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    saleItem(this->selectedItem, slban, money);
                    this->selectedItem = ItemType(-1);
                    slban = 1;
                }
        }
        else if(x >= tru10_.getRect().x && x <= tru10_.getRect().x + tru10_.getRect().w &&
            y >= tru10_.getRect().y && y <= tru10_.getRect().y + tru10_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slban -= 10;
                    if(slban <= 0) slban = 1;
                }
        }
        else if(x >= tru1_.getRect().x && x <= tru1_.getRect().x + tru1_.getRect().w &&
            y >= tru1_.getRect().y && y <= tru1_.getRect().y + tru1_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slban -= 1;
                    if(slban <= 0) slban = 1;
                }
        }
        else if(x >= plus10_.getRect().x && x <= plus10_.getRect().x + plus10_.getRect().w &&
            y >= plus10_.getRect().y && y <= plus10_.getRect().y + plus10_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slban += 10;
                    if(slban >= items[selectedItem]) slban = items[selectedItem];
                }
        }
        else if(x >= plus1_.getRect().x && x <= plus1_.getRect().x + plus1_.getRect().w &&
            y >= plus1_.getRect().y && y <= plus1_.getRect().y + plus1_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slban += 1;
                    if(slban >= items[selectedItem]) slban = items[selectedItem];
                }
        }
        else if(x <= inv_x || x >= inv_x + inv_width ||
            y <= inv_y || y >= inv_y + inv_height){
                this->selectedItem = ItemType(-1);
                slban = 1;
                run = false;
        }
        else {
            this->selectedItem = ItemType(-1);
            slban = 1;
        }
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