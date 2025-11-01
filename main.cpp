#include "include.h"
#include "Texture.h"
#include "game_map.h"
#include "crop.h"
#include "player.h"
#include "Market.h"
#include "TextBox.h"
#include "AccountManager.h"
#include "Login_Interface.h"
#include "ChoosenSeed.h"
#include "Setting.h"

void LoadGame(Player &player , GameMap &gMap_){
    string id = to_string(player.getID());
    ifstream loadFile("savegame/" + id + ".txt");
    if(!loadFile.is_open()){
        cout << "loi! Khong the mo file save. (ID: " << id << ")" << endl;
        return;
    }
    //load player
    string load;
    loadFile >> load;
    player.getID() = stoi(load);
    loadFile >> load;
    player.getname() = load;
    loadFile >> load;
    player.getMoney() = stoi(load);
    //load inventory
    int countType;
    loadFile >> countType;
    player.getInventory().clear();
    for(int i =0; i< countType; i++){
        int itemInt, quantity;
        loadFile >> itemInt >> quantity;
        player.getInventory().addItem(ItemType(itemInt), quantity);
    }
    
    //load map
    int cntcrop;
    loadFile >> cntcrop;
    gMap_.clear();
    for(int i =0; i< cntcrop; i++){
        int x, y, typeInt, stage, timer;
        loadFile >> x >> y >> typeInt >> stage >> timer;
        Crop* newCp = new Crop(CropType(typeInt), y*tile_size, x*tile_size);
        newCp->getGrowthStage() = stage;
        newCp->getGrowthTimer() = timer;
        gMap_.getMap().farmland[x][y] = newCp;
    }
    int end;
    loadFile >> end;
    if(end == -1){
        cout << "load game thanh cong! (ID: " << player.getID() << ")" << endl;
    }
    else{
        cout << "load game that bai!" << endl;
    }
}

void saveGame(Player &player, GameMap &gMap_){
    string id = to_string(player.getID());
    ofstream saveFile("savegame/" + id + ".txt");
    if(!saveFile.is_open()){
        cout << "loi! Khong the tao file save." << endl;
        return;
    }
    //save player
    saveFile << player.getID() << endl;
    saveFile << player.getname() << endl;
    saveFile << player.getMoney() << endl;
    //save inventory
    player.getInventory().save(saveFile);
    //save map
    gMap_.save(saveFile);

    cout << "Game da duoc luu! (ID: " << player.getID() << ")" << endl;
}

int main(int argc, char* argv[]){
     //khoi tao
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 8192);
    SDL_Window *window = SDL_CreateWindow("FARM MAP", SDL_WINDOWPOS_UNDEFINED, 
                                                    SDL_WINDOWPOS_UNDEFINED, 
                                                    screen_width, 
                                                    screen_height, 
                                                    SDL_WINDOW_SHOWN);
    if(!window){
        cout << "loi! Ko tao duoc cua so." << SDL_GetError()<< endl;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout << "loi! Khong the tao renderere. SDL_ERROR " << SDL_GetError() << endl;
    }

    //tai nhac nen
    Mix_Music* music_game = Mix_LoadMUS("sound/farm_theme.wav");
    if(!music_game){
        cout << "loi khong the tai nhac nen!\n";
    }
    else{
        Mix_PlayMusic(music_game, -1);
    }
    Mix_VolumeMusic(64);
    
    //tai font chu
    TTF_Font* font = TTF_OpenFont("font.ttf", 32);

    // account manager
    AccountManager accountManager;

    //gameStage
    gameStage current_gamestage = LOGIN;

    // login screen
    Login_Interface loginInterface(renderer, font);

    //crop
    CropManager::init( renderer);
    CropType current_cropTyppe = CropType::RICE_cp;
    

    //items
    ItemDataBase::init(renderer);

    //player
    Player tvt(renderer, font);

    //market
    Market Market_;

    //setting
    Setting setting_(renderer, font);

    GameMap gMap_;
    gMap_.LoadMap("newmap.txt");
    gMap_.LoadTiles(renderer);

    // choosen seed
    ChoosenSeed choosen_seed(renderer);

    Texture House;
    House.Loadfromfile(renderer, "image_game/House.png");
    House.setRect(tile_size, tile_size, tile_size*5, tile_size*7);

    Texture name;
    name.setRect(10, 10, 100, 30);
    name.write(renderer, font, tvt.getname(), black);

    Texture money;

    Texture icon_inv;
    icon_inv.Loadfromfile(renderer, "image_game/Icon_Inventory.png");
    icon_inv.setRect(screen_width - 70, screen_height - 70, 64, 64);

    Texture icon_market;
    icon_market.Loadfromfile(renderer, "image_game/Icon_Shop.png");
    icon_market.setRect(screen_width - 70, screen_height - 140, 64, 64);

    Texture icon_setting;
    icon_setting.Loadfromfile(renderer, "image_game/Icon_Setting.png");
    icon_setting.setRect(screen_width - 70, screen_height - 210, 64, 64);
   
    //
    int random = 0;
    SDL_StartTextInput(); 
    // loop game
    bool invetorystart = false;
    Uint32 startTime, endTime, TotalTime;
    SDL_Event e;
    bool running = true;
    bool isWindowActive = true; // trang thai cua cua so
    while(running){
        startTime = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) {
                running = false;
                break;
            }
            else if(e.type == SDL_WINDOWEVENT) {
                // xu ly su kien cua so
                if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    isWindowActive = false;
                    cout << "Window lost focus" << endl;
                    // dung nhac
                    Mix_PauseMusic();
                }
                else if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    isWindowActive = true;
                    cout << "Window gained focus" << endl;
                    // tiep tuc nhac
                    Mix_ResumeMusic();
                }
            }
            else if(current_gamestage == PLAYING){
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    int x = (mouseX - root_map_x)/tile_size;
                    int y = (mouseY - root_map_y)/tile_size;

                    if(e.button.button == SDL_BUTTON_LEFT){
                        if(tvt.getStage() == farm){
                            if( mouseX >= icon_inv.getRect().x && mouseX <= icon_inv.getRect().x + icon_inv.getRect().w && 
                                    mouseY >= icon_inv.getRect().y && mouseY <= icon_inv.getRect().y + icon_inv. getRect().h){
                                        tvt.updateStage(inventory);
                            }
                            else if( mouseX >= icon_market.getRect().x && mouseX <= icon_market.getRect().x + icon_market.getRect().w && 
                                    mouseY >= icon_market.getRect().y && mouseY <= icon_market.getRect().y + icon_market. getRect().h){
                                        tvt.updateStage(market);
                            }

                            else if(mouseX >= icon_setting.getRect().x && mouseX <= icon_setting.getRect().x + icon_setting.getRect().w && 
                                    mouseY >= icon_setting.getRect().y && mouseY <= icon_setting.getRect().y + icon_setting. getRect().h){
                                        tvt.updateStage(setting);
                            }
                            else if(choosen_seed.checkclick(mouseX, mouseY)){
                                choosen_seed.xuLyClick(mouseX, mouseY, tvt, current_cropTyppe);
                            }
                            
                            else if((gMap_.getMap().tile[y][x] >=17 && gMap_.getMap().tile[y][x] <= 24 || gMap_.getMap().tile[y][x] == 3) && gMap_.getMap().farmland[y][x] == NULL){
                                int t = current_cropTyppe;
                                if(tvt.getInventory().getQuantity((ItemType)t) > 0){
                                    Crop* newCp = new Crop(current_cropTyppe, x*tile_size, y*tile_size);
                                    gMap_.getMap().farmland[y][x] = newCp;
                                    tvt.getInventory().removeItem((ItemType)t, 1);
                                }
                            }
                            else if(gMap_.getMap().farmland[y][x] != NULL ){
                                if((*(gMap_.getMap().farmland[y][x])).isReadyToHarvest()){
                                    random = startTime%5;
                                    for(const auto item : CropManager::getData(gMap_.getMap().farmland[y][x]->getType()).harvestedItems){
                                        tvt.getInventory().addItem(item, (random == 0)?3:2);
                                    }
                                    delete gMap_.getMap().farmland[y][x];
                                    gMap_.getMap().farmland[y][x] = NULL;
                                }
                            }
                        }
                        else if(tvt.getStage() == inventory){
                            bool check = tvt.getInventory().click(mouseX, mouseY, tvt.getMoney());
                            if(!check) tvt.updateStage(farm); 
                        } 
                        else if(tvt.getStage() == market){
                            bool check = Market_.click(mouseX, mouseY,tvt.getInventory(), tvt.getMoney());
                            if(!check) tvt.updateStage(farm);
                        }  
                        else if(tvt.getStage() == setting){
                            if(setting_.checkLogOut(mouseX, mouseY)) {
                                current_gamestage = LOGIN;
                            }

                            if(setting_.checkSaveGame(mouseX, mouseY)) {
                                saveGame(tvt, gMap_);
                                //can them ghi chu save thanh cong
                            }

                            if(setting_.xulyAmThanh(mouseX, mouseY)) {
                                Mix_VolumeMusic(setting_.getVolume());
                            }
                            
                            setting_.get_renameTextBox().setActive(setting_.get_renameTextBox().checkClick(mouseX, mouseY));
                            if(setting_.checkRenameOK(mouseX, mouseY)){
                                setting_.xulyRename(tvt, renderer, font);
                                name.write(renderer, font, tvt.getname(), black);
                            }

                            if(setting_.checkOutSetting(mouseX, mouseY)){
                                setting_.get_renameTextBox().clearText();
                                tvt.updateStage(farm);
                            }
                        } 
                        
                    }
                    if(e.button.button == SDL_BUTTON_RIGHT){
                        //tvt.updateStage(farm);
                        // current_gamestage = LOGIN;
                        //tvt.updateStage(setting);
                        // saveGame(tvt, gMap_);
                    }
                }
                else if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_s){
                        root_map_y -= tile_size/2;
                        if(root_map_y <= 960 - 64*tile_size) root_map_y = 960 - 64*tile_size;
                    } 
                    else if(e.key.keysym.sym == SDLK_w){
                        root_map_y += tile_size/2;
                        if(root_map_y >= 0) root_map_y = 0;
                    }
                    else if(e.key.keysym.sym == SDLK_d){
                        root_map_x -= tile_size/2;
                        if(root_map_x <= 1600 - 64*tile_size) root_map_x = 1600 - 64*tile_size;
                    }
                    else if(e.key.keysym.sym == SDLK_a){
                        root_map_x += tile_size/2;
                        if(root_map_x >= 0) root_map_x = 0;
                    }
                }

                //
                if(tvt.getStage() == setting){
                    setting_.get_renameTextBox().handleEvent(e);
                    if(setting_.get_renameTextBox().getText() != ""){
                        setting_.set_isRenameOK(true);
                    }
                    else setting_.set_isRenameOK(false);
                }
            }
            else if(current_gamestage == LOGIN){
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    if(e.button.button == SDL_BUTTON_LEFT){
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;
                        //kiem tra co chon o nay khong
                        loginInterface.getUsernameBox().setActive(loginInterface.getUsernameBox().checkClick(mouseX, mouseY));
                        loginInterface.getPasswordBox().setActive(loginInterface.getPasswordBox().checkClick(mouseX, mouseY));
                        //kiem tra co bam nut login/register/enter khong
                        if(loginInterface.checkClick(mouseX, mouseY)){
                            if(loginInterface.getLoginButtonHover()){
                                //login
                                int userID = accountManager.login(loginInterface.getUsernameBox().getText(), loginInterface.getPasswordBox().getText());
                                if(userID != -1){
                                    tvt.getID() = userID;
                                    LoadGame(tvt, gMap_);
                                    setting_.reLoadAccountSetting(tvt, renderer, font, loginInterface.getUsernameBox().getText());
                                    name.write(renderer, font, tvt.getname(), black);
                                    current_gamestage = PLAYING;
                                }
                                else{
                                    cout << "Dang nhap that bai! Vui long kiem tra lai tai khoan." << endl;
                                }
                                loginInterface.getUsernameBox().clearText(); loginInterface.getUsernameBox().setActive(false);
                                loginInterface.getPasswordBox().clearText(); loginInterface.getPasswordBox().setActive(false);
                            }
                            else{
                                //register
                                bool success = accountManager.registerAccount(loginInterface.getUsernameBox().getText(), loginInterface.getPasswordBox().getText());
                                if(success){
                                    cout << "Dang ky thanh cong! Ban co the dang nhap bang tai khoan vua tao." << endl;
                                }
                                else{
                                    cout << "Dang ky that bai! Tai khoan da ton tai." << endl;
                                }
                            }
                        }
                    }
                    else if(e.button.button == SDL_BUTTON_RIGHT){
                        current_gamestage = PLAYING;
                    }
                }

                //xu ly van ban
                loginInterface.getUsernameBox().handleEvent(e);
                loginInterface.getPasswordBox().handleEvent(e);
            }
        }

        if(!running) break;

        else if(isWindowActive){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // mau nen (den)
            SDL_RenderClear(renderer);

            if(current_gamestage == PLAYING){
                gMap_.DrawMap(renderer);

                for(int i = 0; i < max_map_y ; i++){
                    for(int j =0 ; j < max_map_x; j++){
                        if(gMap_.getMap().farmland[i][j] != NULL){
                            gMap_.getMap().farmland[i][j]->update(40);
                            gMap_.getMap().farmland[i][j]->render(renderer) ;
                        }
                    }
                }
                House.setRect(tile_size + root_map_x, tile_size + root_map_y, tile_size*5, tile_size*7);
                House.render(renderer);
                name.FillRect(renderer, white);
                name.render(renderer);
                string mn = "$" + to_string(tvt.getMoney());
                money.write(renderer, font, mn, yellow);
                money.setRect(130, 10, mn.size()*14, 30);
                money.render(renderer);

                //
                icon_inv.render(renderer);
                icon_market.render(renderer);
                icon_setting.render(renderer);

                //
                if(tvt.getStage() == farm){
                    choosen_seed.render(renderer, font, tvt, current_cropTyppe);
                }

                //
                if(tvt.getStage() == inventory){
                    tvt.getInventory().render(renderer, font);
                }
                if(tvt.getStage() == market){
                    Market_.render(renderer, font);
                }
                if(tvt.getStage() == setting){
                    setting_.render(renderer, font);
                }
            }
            else if(current_gamestage == LOGIN){
                loginInterface.render(renderer, font);
            }

            SDL_RenderPresent(renderer);

            endTime = SDL_GetTicks();
            TotalTime = endTime - startTime;
            //cout << TotalTime <<endl;
            SDL_Delay((40 - TotalTime > 0)?40 - TotalTime: 0);
        }
        else {
            for(int i = 0; i < max_map_y ; i++){
                for(int j =0 ; j < max_map_x; j++){
                    if(gMap_.getMap().farmland[i][j] != NULL){
                        gMap_.getMap().farmland[i][j]->update(500);
                    }
                }
            }
            //cout << "Delay" << endl;
            SDL_Delay(500);
        }
        
        
    }

    //save game
    saveGame(tvt, gMap_);

    SDL_StopTextInput();
    TTF_CloseFont(font);
    font = NULL;

    Mix_FreeMusic(music_game);
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;
}