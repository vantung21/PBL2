#include "ChoosenSeed.h"

ChoosenSeed::ChoosenSeed(SDL_Renderer *renderer){
    areaItemSelection.setRect(128, screen_height - 100, 64*5, 94);
    openChoosenSeed.Loadfromfile(renderer, "image_game/open_choosenSeed.png");
    openChoosenSeed.setRect(128, screen_height - 32 , 64, 32);
    arrowLeft.Loadfromfile(renderer, "image_game/arrow_left.png");
    arrowLeft.setRect(64, screen_height - 85 , 64, 64);   
    arrowRight.Loadfromfile(renderer, "image_game/arrow_right.png");
    arrowRight.setRect(64 + 64*6, screen_height - 85 , 64, 64);
    
    itemOffset = 0;
    selectedIndex = -1;
    isOpen = false;
}

vector<ItemType> ChoosenSeed::getAvailableSeeds(Player &tvt) {
    vector<ItemType> items;
    for (int i = 0; i < COUNT_SEED; i++) {
        ItemType it = ItemType(i);
        if (tvt.getInventory().getQuantity(it) > 0) {
            items.push_back(it);
        }
    }
    return items;
}

// Tim vi tri cua item trong vector availableItems
int ChoosenSeed::findItemIndex(const vector<ItemType>& items, const ItemType& item) {
    for (int i = 0; i < items.size(); ++i) {
        if (items[i] == item) {
            return i;
        }
    }
    return -1; // khong tim thay
}


bool ChoosenSeed::checkclick(int x, int y){
    if(isOpen){
        // neu click vao khu vuc chon hat giong
        if (x  >= arrowLeft.getRect().x && x  <= arrowRight.getRect().x + arrowRight.getRect().w &&
            y  >= areaItemSelection.getRect().y && y  <= areaItemSelection.getRect().y + areaItemSelection.getRect().h) {
            return true;
        }   
        else if (x >= openChoosenSeed.getRect().x && x <= openChoosenSeed.getRect().x + openChoosenSeed.getRect().w &&
            y >= openChoosenSeed.getRect().y && y <= openChoosenSeed.getRect().y + openChoosenSeed.getRect().h){
            return true;
        }
    }
    else {
        // click vao tat khung chon hat giong
        if(x >= openChoosenSeed.getRect().x && x <= openChoosenSeed.getRect().x + openChoosenSeed.getRect().w &&
           y >= openChoosenSeed.getRect().y && y <= openChoosenSeed.getRect().y + openChoosenSeed.getRect().h){
            return true;
        }
    }
    return false;
}

void ChoosenSeed::xuLyClick(int x, int y, Player &tvt , CropType &current_cropType){
    if(isOpen){
        // kiem tra co click vao tat khung chon hat hay k
        if(x >= openChoosenSeed.getRect().x && x <= openChoosenSeed.getRect().x + openChoosenSeed.getRect().w &&
           y >= openChoosenSeed.getRect().y && y <= openChoosenSeed.getRect().y + openChoosenSeed.getRect().h){
            
            isOpen = false;
            openChoosenSeed.setRect(128, screen_height - 32 , 64, 32);
            return; 
        }

        // lay danh sach cac hat giong dang co
        availableItems = getAvailableSeeds(tvt);

        // neu k co hat giong nao thi thoat
        if (availableItems.empty()) {
            selectedIndex = -1;
            itemOffset = 0;
            return;
        } 

        //kiem tra selectedIndex khong hop le hoac không khop current_cropType
        // actualIndex: chi so thuc te cua Item trong toan bo availableItems = chi so bat dau + chi so trong khung
        int actualIndex = itemOffset + selectedIndex;
        if (selectedIndex == -1 || actualIndex >= availableItems.size() || availableItems[actualIndex] != ItemType(current_cropType)) 
        {
            // Tim vi tri cua current_cropType trong vector
            int foundIndex = findItemIndex(availableItems, ItemType(current_cropType));
            
            if (foundIndex != -1) {
                actualIndex = foundIndex;
                itemOffset = max(0, min(actualIndex, (int)availableItems.size() - 5)); 
                selectedIndex = actualIndex - itemOffset;
            } 
            // khong thay thi chon hat dau tien trong vector
            else {
                selectedIndex = 0;
                itemOffset = 0;
                current_cropType = CropType(availableItems[0]); 
            }
        }

        
        int baseX = areaItemSelection.getRect().x;
        // mui ten trai
        if(x >= arrowLeft.getRect().x && x <= arrowLeft.getRect().x + arrowLeft.getRect().w &&
           y >= arrowLeft.getRect().y && y <= arrowLeft.getRect().y + arrowLeft.getRect().h){
            
            if (selectedIndex > 0) {
                selectedIndex--;
            } 
            else if (itemOffset - 4 > 0) {
                itemOffset -= 5;
                selectedIndex = 4;
            }
            current_cropType = CropType(availableItems[itemOffset + selectedIndex]);
        }
        // mui ten phai
        else if(x >= arrowRight.getRect().x && x <= arrowRight.getRect().x + arrowRight.getRect().w &&
                y >= arrowRight.getRect().y && y <= arrowRight.getRect().y + arrowRight.getRect().h){

            if (selectedIndex < 4 && (itemOffset + selectedIndex + 1) < availableItems.size()) {
                selectedIndex++;
            } 
            else if (itemOffset + 5 < availableItems.size()) {
                itemOffset += 5;
                selectedIndex = 0;
            }
            current_cropType = CropType(availableItems[itemOffset + selectedIndex]);
        }
        // Click vao icon
        else {
            for (int displayIndex = 0; displayIndex < 5; displayIndex++) {
                int i = itemOffset + displayIndex; 
                if (i >= availableItems.size()) break; 

                ItemType it = availableItems[i];
                int iconX1 = baseX + displayIndex * 64;
                int iconX2 = iconX1 + 64;
                
                if (x >= iconX1 && x <= iconX2) {
                    current_cropType = CropType(it); 
                    selectedIndex = displayIndex; 
                    break; 
                }
            }
        }
    } 
    else { 
        isOpen = true;
        openChoosenSeed.setRect(128, screen_height - 132 , 64, 32);
        
        availableItems = getAvailableSeeds(tvt);

        if (availableItems.empty()) {
            selectedIndex = -1;
            itemOffset = 0;
        } 
        else {
            int foundIndex = findItemIndex(availableItems, ItemType(current_cropType));
            
            if (foundIndex != -1) {
                int actualIndex = foundIndex;
                itemOffset = max(0, min(actualIndex, (int)availableItems.size() - 5));
                selectedIndex = actualIndex - itemOffset;
            } else {
                selectedIndex = 0;
                itemOffset = 0;
                current_cropType = CropType(availableItems[0]);
            }
        }
    }
}

void ChoosenSeed::render(SDL_Renderer *renderer, TTF_Font *font, Player &tvt, CropType &current_cropType){
    if(isOpen){
        areaItemSelection.FillRect(renderer, gray);
        areaItemSelection.drawRect(renderer, black); 
        arrowLeft.render(renderer);
        arrowRight.render(renderer);
        int x_icon = 128;
        int y_icon = screen_height - 100;

        availableItems = getAvailableSeeds(tvt);

        
        for(int displayIndex = 0; displayIndex < 5; displayIndex++){
            int i = itemOffset + displayIndex; 
            if (i >= availableItems.size()) break; // het item de ve

            ItemType it = availableItems[i]; 

            // highlight neu dc chon
            if(current_cropType == CropType(it)){
                Texture highlight;
                highlight.setRect(x_icon, y_icon, 64, 94);
                highlight.FillRect(renderer, orange);
                highlight.drawRect(renderer, black);
            }

            ItemDataBase::allItems[it].icon.setRect(x_icon, y_icon, 64, 64);
            ItemDataBase::allItems[it].icon.render(renderer);

            Texture qtyText;
            string qty = "x" + to_string(tvt.getInventory().getQuantity(it));
            qtyText.write(renderer, font, qty, black);
            qtyText.setRect(x_icon + 32 - (qty.size()*12)/2, y_icon + 70, qty.size()*12, 20);
            qtyText.render(renderer);

            x_icon += 64;
        }

        openChoosenSeed.render(renderer);
    } 
    else {
        openChoosenSeed.render(renderer);
    }
}