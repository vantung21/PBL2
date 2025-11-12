#include "Water.h"

Water::Water(SDL_Renderer* renderer, TTF_Font *font) : Tool(false) {
    water.Loadfromfile(renderer, "image_game/Water.png");
    watering.Loadfromfile(renderer, "image_game/Watering.png");
    w_x = 10;
    w_y = screen_height - 200;
    quantity = 10;
    isWatering = false;
    loop = 5;
    currTime = 0;
    water.setRect(w_x, w_y, 64, 64);
    quantityTexture.write(renderer, font, to_string(quantity), black);
    int len = quantityTexture.getRect().w*20/quantityTexture.getRect().h;
    quantityTexture.setRect(w_x + water.getRect().w/2 - len/2, w_y + water.getRect().h, len, 20);
    bgW.setRect(w_x, w_y, 64, 64 + quantityTexture.getRect().h);
}

void Water::render(SDL_Renderer* renderer) {
    bgW.drawRect(renderer, black);
    if(isWatering){
        watering.render(renderer);
        loop--;
        if(loop < 0){
            isWatering = false;
            loop = 5;
        }
    }
    else{
        water.render(renderer);
    }
    quantityTexture.render(renderer);
}
void Water::setPos(int x, int y) {
    water.setRect(x - water.getRect().w/4, y - water.getRect().h/3, water.getRect().w, water.getRect().h);
    watering.setRect(x - water.getRect().w/4, y - water.getRect().h, water.getRect().w, water.getRect().h);
}

bool Water::checkClick(int x, int y) {
    return (x > w_x && x < w_x + water.getRect().w &&
            y > w_y && y < w_y + water.getRect().h);
}

void Water::drop() {
    setHold(false);
    water.setRect(w_x, w_y, water.getRect().w, water.getRect().h);
}

int Water::getQuantity(){
    return this->quantity;
}

void Water::setQuantity(int sl){
    this->quantity = sl;
}

void Water::Watering(){
    this->quantity--;
    isWatering = true;
    
}

void Water::updateQuatity(SDL_Renderer* renderer, TTF_Font *font, int x){
    currTime += x;
    if(currTime >= recoveryTime){
        quantity += 2;
        if(quantity >= maxQuantity){
            quantity = maxQuantity;
        }
        currTime = currTime - recoveryTime;
    }
    quantityTexture.write(renderer, font, to_string(quantity), black);
    int len = quantityTexture.getRect().w*20/quantityTexture.getRect().h;
    quantityTexture.setRect(w_x + water.getRect().w/2 - len/2, w_y + water.getRect().h, len, 20);
}