#include "player.h"


Player::Player(int initialMoney) : money(initialMoney) {
    inventory.addItem(RICE_SEED, 10);
    inventory.addItem(CARROT_SEED, 3);
    inventory.addItem(CORN_SEED, 2); 
}
void Player::update() {
    // Update player state if needed
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