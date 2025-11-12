#include "player.h"


Player::Player(SDL_Renderer* renderer, TTF_Font* font, int ID, const string name, int initialMoney)
: player_ID(ID), money(initialMoney), playername(name), inventory(renderer, font){

    this->stage = farm;
    inventory.addItem(RICE_SEED, 5);
    inventory.addItem(CARROT_SEED, 2);

    level = 1;
    exp = 0;
    
    levelTexture.write(renderer, font, to_string(level), black);
    levelTexture.setRect(10, 10, 50, 50);
    
    //nameTexture.write(renderer, font, playername, black);
    nameTexture.setRect(levelTexture.getRect().x + levelTexture.getRect().w , 10, 200, 35);
    nameText.write(renderer, font, playername, black);
    int len = nameText.getRect().w*(nameTexture.getRect().h - 4)/nameText.getRect().h;
    nameText.setRect(nameTexture.getRect().x + 5, nameTexture.getRect().y + 2, len, nameTexture.getRect().h - 4);

    expTexture.setRect(levelTexture.getRect().x + levelTexture.getRect().w, 45, nameTexture.getRect().w, 15);
    currExp.setRect(expTexture.getRect().x, expTexture.getRect().y, expTexture.getRect().w*exp/(50+level*50), expTexture.getRect().h);

    //moneyTexture.
    string temp = "$" + to_string(money);
    moneyTexture.write(renderer, font, temp, black);
    len = moneyTexture.getRect().w*35/moneyTexture.getRect().h;
    moneyTexture.setRect(nameTexture.getRect().x + nameTexture.getRect().w + 20, 10, len, 35);

}
void Player::updateStage(playerStage st) {
    this->stage = st;
}

void Player::updateExp(SDL_Renderer *renderer, TTF_Font* font, Rain &rain_, int x){
    this->exp += x;
    while(this->exp >= (50+50*this->level)){
        this->exp -= (50+50*this->level);
        level++;
        if(level%3 == 0){
            rain_.setIsRaining(true);
            rain_.resetCurrTime();
        }
    } 
    levelTexture.write(renderer, font, to_string(level), black);
    levelTexture.setRect(10, 10, 50, 50);

    currExp.setRect(expTexture.getRect().x, expTexture.getRect().y, expTexture.getRect().w*exp/(50+level*50), expTexture.getRect().h);
}
void Player::update_nameText(SDL_Renderer *renderer, TTF_Font* font){
    nameText.write(renderer, font, playername, black);
    int len = nameText.getRect().w*(nameTexture.getRect().h - 4)/nameText.getRect().h;
    nameText.setRect(nameTexture.getRect().x + 5, nameTexture.getRect().y + 2, len, nameTexture.getRect().h - 4);
}
void Player::update_moneyTexture(SDL_Renderer *renderer, TTF_Font* font){
    string temp = "$" + to_string(money);
    moneyTexture.write(renderer, font, temp, black);
    int len = moneyTexture.getRect().w*35/moneyTexture.getRect().h;
    moneyTexture.setRect(nameTexture.getRect().x + nameTexture.getRect().w + 20, 10, len, 35);
}

playerStage Player::getStage(){
    return this->stage;
}

void Player::render(SDL_Renderer *renderer) {
    
    // Render player graphics if needed
    levelTexture.FillRect(renderer, d_yellow);
    levelTexture.render(renderer);
    levelTexture.drawRect(renderer, black);

    nameTexture.FillRect(renderer, d_yellow);
    nameTexture.drawRect(renderer, black);
    nameText.render(renderer);
    
    expTexture.FillRect(renderer, gray);
    currExp.FillRect(renderer, l_blue);
    expTexture.drawRect(renderer, black);
    
    moneyTexture.FillRect(renderer, d_yellow);
    moneyTexture.render(renderer);
    moneyTexture.drawRect(renderer, black);

}

int& Player::getMoney(){
    return this->money;
}

Inventory& Player::getInventory(){
    return this->inventory;
}

string& Player::getname(){
    return playername;
}

void Player::clear(){
    playername = "player";
    money = 10;
    level = 1;
    exp = 0;
}