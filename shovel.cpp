#include "shovel.h"

Shovel::Shovel(SDL_Renderer* renderer) : Tool(false) {
    shovel.Loadfromfile(renderer, "image_game/shovel.png");
    s_x = 10;
    s_y = screen_height - 100;
    loop = 0;
    is_shoveling = false;
    shovel.setRect(s_x, s_y, 60, 80);
    bgS.setRect(s_x, s_y, 60, 80);
}
void Shovel::render(SDL_Renderer* renderer) {
    if(this->hold){
        bgS.drawRect(renderer, black);
    }
    if(is_shoveling){
        shovel.setRect(shovel.getRect().x - shovel.getRect().w/60, shovel.getRect().y + shovel.getRect().h/20);
        loop--;
        if(loop <= 0) is_shoveling = false;
    }
    shovel.render(renderer);
}
void Shovel::setPos(int x, int y) {
    shovel.setRect(x - shovel.getRect().w/4, y - shovel.getRect().h, shovel.getRect().w, shovel.getRect().h);
}
bool Shovel::checkClick(int x, int y) {
    return (x > s_x && x < s_x + shovel.getRect().w &&
            y > s_y && y < s_y + shovel.getRect().h);
}

void Shovel::drop() {
    setHold(false);
    shovel.setRect(s_x, s_y, shovel.getRect().w, shovel.getRect().h);
}

void Shovel::shoveling(){
    is_shoveling = true;
    loop = 5;
}
