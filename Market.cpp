#include "Market.h"

Market::Market(){
    for(int c = RICE_SEED; c < COUNT; c++){
        this->itemForSale.push_back(ItemType(c));
    }
    slmua = 1;
    selectedItem = ItemType(-1);
    mrk_x = screen_width/8;
    mrk_y = screen_height/8;
    mrk_height = screen_height*6/8;
    mrk_width = screen_width*6/8; 
}

bool Market :: buyItem(ItemType item, int quantity, Inventory &playerInvenetory, int &playerMoney){
    int price = ItemDataBase::allItems.at(item).buyPrice*quantity;
    if(playerMoney >= price){
        playerInvenetory.addItem(item, quantity);
        playerMoney -= price;
        return true;
    }
    return false;
}

void Market :: render(SDL_Renderer *renderer, TTF_Font *font){
    // load anh nen
    Texture bgInventory;
    bgInventory.Loadfromfile(renderer, "image_game/BG_Inventory2.png");
    bgInventory.setRect(mrk_x,mrk_y, mrk_width, mrk_height);
    bgInventory.render(renderer);
    bgInventory.drawRect(renderer, black);

    // ve tieu de
    Texture titleInv;
    titleInv.write(renderer, font, "MARKET" , black);
    titleInv.setRect((mrk_x + mrk_width/2 - 64*2), (mrk_y+32), 64*4, 64);
    titleInv.render(renderer);

    Texture line;
    line.setRect(mrk_x + mrk_width/2 - 64*2 - 32, mrk_y + 106, 64*5, 4);
    line.FillRect(renderer, black);


    // ve cac items
    int item_x = mrk_x + 10, item_y = mrk_y + 126;
    itemPositions.clear();
    for(auto &item : itemForSale){
        //luu vi tri cac item trong inv
        itemPositions[item].setRect(item_x, item_y, 100, 100+30);

        // highlight o duoc chon
        if(selectedItem == item){
            itemPositions[item].FillRect(renderer, yellow);
            itemPositions[item].drawRect(renderer, black);
        }

        //ve item
        ItemDataBase::allItems[item].icon.setRect(item_x, item_y, 100, 100);
        ItemDataBase::allItems[item].icon.render(renderer);

        //ve so luong
        string s = "$" + to_string(ItemDataBase::allItems[item].buyPrice);
        int lenght = s.size();
        Texture giamua;
        giamua.write(renderer, font, s, black);
        giamua.setRect(item_x + (100-14*lenght)/2, item_y + 100, 14*lenght, 30);
        giamua.FillRect(renderer, white);
        giamua.drawRect(renderer, black);  
        giamua.render(renderer);

        //dieu chinh vi tri cho o tiep theo
        item_x += 100;
        if(item_x > mrk_x + mrk_width- 110){
            item_x = mrk_x + 10;
            item_y += 140;
        }   
    }

    //ve khu vuc mua hang
    Texture areaSbuy;
    areaSbuy.setRect(mrk_x, mrk_y + mrk_height - 140, mrk_width, 140);
    areaSbuy.FillRect(renderer, gray);
    areaSbuy.drawRect(renderer, black);

    //
    if(selectedItem != ItemType(-1)){
        string select = "Selected: ";
        select += ItemDataBase::allItems[selectedItem].ItemName
                + "    Price: " 
                + to_string(ItemDataBase::allItems[selectedItem].buyPrice);
        
        Texture firstline;
        firstline.write(renderer, font, select, black);
        firstline.setRect(mrk_x + 32, mrk_y + mrk_height - 120, select.size()*16, 40);
        firstline.render(renderer);

        //
        string quantity = "Quantity: ";
        Texture sl;
        sl.write(renderer, font, quantity, black);
        sl.setRect(mrk_x + 32, mrk_y + mrk_height - 60, quantity.size()*16, 40);
        sl.render(renderer);
        //ve nut + -
        string plus10 = "+10";
        string plus1 = "+1";
        string tru10 = "-10";
        string tru1 = "-1";
        tru10_.write(renderer, font, tru10, black);
        tru10_.setRect(mrk_x + 32 + quantity.size()*16, mrk_y + mrk_height - 60, 3*16, 40);
        tru10_.FillRect(renderer, red);
        tru10_.drawRect(renderer, black);
        tru10_.render(renderer);

        tru1_.write(renderer, font, tru1, black);
        tru1_.setRect(mrk_x + 32 + quantity.size()*16 + 4*16, mrk_y + mrk_height - 60, 3*16, 40);
        tru1_.FillRect(renderer, red);
        tru1_.drawRect(renderer, black);
        tru1_.render(renderer);

        plus1_.write(renderer, font, plus1, black);
        plus1_.setRect(mrk_x + 32 + quantity.size()*16 +  14*16, mrk_y + mrk_height - 60, 3*16, 40);
        plus1_.FillRect(renderer, red);
        plus1_.drawRect(renderer, black);
        plus1_.render(renderer);

        plus10_.write(renderer, font, plus10, black);
        plus10_.setRect(mrk_x + 32 + quantity.size()*16 + 18*16, mrk_y + mrk_height - 60, 3*16, 40);
        plus10_.FillRect(renderer, red);
        plus10_.drawRect(renderer, black);
        plus10_.render(renderer);

        sl.write(renderer, font, to_string(slmua), blue);
        sl.setRect(mrk_x + 32 + quantity.size()*16 + 7*16 + (7-to_string(slmua).size())*16/2, mrk_y + mrk_height - 60, to_string(slmua).size()*16, 35);
        sl.render(renderer);
        sl.setRect(mrk_x + 32 + quantity.size()*16 + 7*16 + 8, mrk_y + mrk_height - 60 + 38, 6*16, 2);
        sl.FillRect(renderer, black);

        int t = slmua*ItemDataBase::allItems[selectedItem].buyPrice;
        string tong = "Total Cost: ";
        tong += to_string(t);
        sl.write(renderer, font, tong, black);
        sl.setRect(mrk_x + mrk_width - 20*16, mrk_y + mrk_height - 120, tong.size()*16, 40);
        sl.render(renderer);

        string buy = " BUY ";
        buy_.write(renderer, font, buy, black);
        buy_.setRect(mrk_x + mrk_width - 12*16, mrk_y + mrk_height - 70, 6*16, 60);
        buy_.FillRect(renderer, green);
        buy_.drawRect(renderer, black);
        buy_.render(renderer);
    }  
    // anh truong dap trai
}


ItemType Market::getItemAtPosition(int x, int y){
    for( auto& pair : itemPositions){
        if(x >= pair.second.getRect().x && x <= pair.second.getRect().x + pair.second.getRect().w &&
           y >= pair.second.getRect().y && y <= pair.second.getRect().y + pair.second.getRect().h)
            return pair.first;
    }
    return ItemType(-1);
}

bool Market::click(int x, int y,Inventory &inventory, int &money){
    bool run = true;
    ItemType clickedItem = getItemAtPosition(x, y);
    if(clickedItem != ItemType(-1)){
        this->selectedItem = clickedItem;
    }
    else{
        if(x >= buy_.getRect().x && x <= buy_.getRect().x + buy_.getRect().w &&
            y >= buy_.getRect().y && y <= buy_.getRect().y + buy_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    buyItem(this->selectedItem, slmua, inventory, money);
                    this->selectedItem = ItemType(-1);
                    this->slmua = 1;
                }
        }
        else if(x >= tru10_.getRect().x && x <= tru10_.getRect().x + tru10_.getRect().w &&
            y >= tru10_.getRect().y && y <= tru10_.getRect().y + tru10_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slmua -= 10;
                    if(slmua <= 0) slmua = 1;
                }
        }
        else if(x >= tru1_.getRect().x && x <= tru1_.getRect().x + tru1_.getRect().w &&
            y >= tru1_.getRect().y && y <= tru1_.getRect().y + tru1_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slmua -= 1;
                    if(slmua <= 0) slmua = 1;
                }
        }
        else if(x >= plus10_.getRect().x && x <= plus10_.getRect().x + plus10_.getRect().w &&
            y >= plus10_.getRect().y && y <= plus10_.getRect().y + plus10_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slmua += 10;
                    if(slmua >= 999) slmua = 999;
                }
        }
        else if(x >= plus1_.getRect().x && x <= plus1_.getRect().x + plus1_.getRect().w &&
            y >= plus1_.getRect().y && y <= plus1_.getRect().y + plus1_.getRect().h){
                if(this->selectedItem != ItemType(-1)){
                    slmua += 1;
                    if(slmua >= 999) slmua = 999;
                }
        }
        else if(x <= mrk_x || x >= mrk_x + mrk_width ||
            y <= mrk_y || y >= mrk_y + mrk_height){
                this->selectedItem = ItemType(-1);
                slmua = 1;
                run = false;
        }
        else {
            this->selectedItem = ItemType(-1);
            slmua = 1;
        }
    }
    return run;
}
