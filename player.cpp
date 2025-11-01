#include "player.h"


Player::Player(SDL_Renderer* renderer, TTF_Font* font, int ID, const string name, int initialMoney) : player_ID(ID), money(initialMoney), playername(name) {
    this->stage = farm;
    inventory.addItem(RICE_SEED, 10);
    inventory.addItem(CARROT_SEED, 3);
    inventory.addItem(CORN_SEED, 2); 

    level = 1;
    exp = 0;

    levelTexture.write(renderer, font, to_string(level), black);
    levelTexture.setRect(10, 10, 50, 50);
    
    //nameTexture.write(renderer, font, playername, black);
    nameTexture.setRect(60, 10, 400, 30);

    string temp = to_string(exp) + "/" + to_string(50 + level*50);
    expTexture.write(renderer, font, temp, black);
    expTexture.setRect(60, 45, 400, 15);

    //moneyTexture.
}
void Player::updateStage(playerStage st) {
    this->stage = st;
}

playerStage Player::getStage(){
    return this->stage;
}

void Player::render(SDL_Renderer *renderer) {
    
    // Render player graphics if needed
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