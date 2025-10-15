#include "player.h"


Player::Player(int ID, const string name, int initialMoney) : player_ID(ID), money(initialMoney), playername(name) {
    this->stage = farm;
    inventory.addItem(RICE_SEED, 10);
    inventory.addItem(CARROT_SEED, 3);
    inventory.addItem(CORN_SEED, 2); 
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

string Player::getname() const{
    return playername;
}