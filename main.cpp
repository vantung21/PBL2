#include "include.h"
#include "Texture.h"
#include "game_map.h"
#include "crop.h"
#include "player.h"
#include "Market.h"
#include "TextBox.h"
#include "AccountManager.h"
#include "Login_Interface.h"

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
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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
    
    //tai font chu
    TTF_Font* font = TTF_OpenFont("font.ttf", 32);

    // account manager
    AccountManager accountManager;

    //gameStage
    gameStage current_gamestage = LOGIN;

    // login screen

    Login_Interface loginInterface(renderer, font);
    // Texture login_bg;
    // login_bg.Loadfromfile(renderer, "image_game/LOGIN_BG.png");
    // login_bg.setRect(0, 0 , screen_width, screen_height);
    // Texture login_box;
    // login_box.Loadfromfile(renderer, "image_game/board_login.png");
    // login_box.setRect(0, 0 , screen_width, screen_height);

    // Texture login_button;
    // login_button.write(renderer, font, " LOGIN " , black);
    // login_button.setRect(screen_width/2 -200, screen_height/2 + 10, 180, 60);

    // Texture register_button;
    // register_button.write(renderer, font, "REGISTER" , black);
    // register_button.setRect(screen_width/2 + 20, screen_height/2 + 10, 180, 60);

    // bool login_button_hover = true;

    // Texture enter_button;
    // enter_button.write(renderer, font, " ENTER " , black);
    // enter_button.setRect(screen_width/2 -100, screen_height/2 + 220, 200, 60);

    // TextBox usernameBox("Username", screen_width/2 - 200, screen_height/2 + 80, 400, 50);
    // TextBox passwordBox("Password", screen_width/2 - 200, screen_height/2 + 150, 400, 50);

    //crop
    CropManager :: init( renderer);
    CropType current_cropTyppe = CropType :: RICE_cp;

    //items
    ItemDataBase::init(renderer);

    //player
    Player tvt;

    //market
    Market Market_;

    GameMap gMap_;
    gMap_.LoadMap("newmap.txt");
    gMap_.LoadTiles(renderer);

    //khu vuc chon hat giong
    Texture areaItemSelection;
    areaItemSelection.setRect(128, screen_height - 100, 64*5, 94);
    Texture arrowLeft, arrowRight;
    arrowLeft.Loadfromfile(renderer, "image_game/arrow_Left.png");
    arrowLeft.setRect(64, screen_height - 85 , 64, 64);  
    arrowRight.Loadfromfile(renderer, "image_game/arrow_Right.png");
    arrowRight.setRect(64 + 64*6, screen_height - 85 , 64, 64);
    int itemOffset = 0; // chi so cua ItemType dau tien dc hien thi
    int displayIndex = 0; // dung de ve cac icon 

    Texture House;
    House.Loadfromfile(renderer, "image_game/House.png");
    House.setRect(tile_size, tile_size, tile_size*5, tile_size*7);
    Texture name;

    Texture icon_inv;
    icon_inv.Loadfromfile(renderer, "image_game/Icon_Inventory.png");
    icon_inv.setRect(screen_width - 70, screen_height - 70, 64, 64);

    Texture icon_market;
    icon_market.Loadfromfile(renderer, "image_game/Icon_Shop.png");
    icon_market.setRect(screen_width - 70, screen_height - 140, 64, 64);


    name.setRect(10, 10, 100, 30);
    name.write(renderer, font, tvt.getname(), black);
    Texture money;
    //money.setRect(110, 10, 30, 30);

    int random = 0;
    SDL_StartTextInput(); 
    // loop game
    bool invetorystart = false;
    Uint32 startTime, endTime, TotalTime;
    SDL_Event e;
    bool running = true;
    while(running){
        startTime = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            else if(current_gamestage == PLAYING){
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    int x= (e.button.x - root_map_x)/tile_size;
                    int y= (e.button.y - root_map_y)/tile_size;
                    if(e.button.button == SDL_BUTTON_LEFT){
                        if(tvt.getStage() == farm){
                            if( e.button.x >= icon_inv.getRect().x && e.button.x <= icon_inv.getRect().x + icon_inv.getRect().w && 
                                    e.button.y >= icon_inv.getRect().y && e.button.y <= icon_inv.getRect().y + icon_inv. getRect().h){
                                        tvt.updateStage(inventory);
                            }
                            else if( e.button.x >= icon_market.getRect().x && e.button.x <= icon_market.getRect().x + icon_market.getRect().w && 
                                    e.button.y >= icon_market.getRect().y && e.button.y <= icon_market.getRect().y + icon_market. getRect().h){
                                        tvt.updateStage(market);
                            }
                            // chon hat giong khac
                            else if (e.button.x  >= areaItemSelection.getRect().x - 64 && e.button.x  <= areaItemSelection.getRect().x + areaItemSelection.getRect().w + 64 &&
                                     e.button.y  >= areaItemSelection.getRect().y && e.button.y  <= areaItemSelection.getRect().y + areaItemSelection.getRect().h) {
                                int baseX = areaItemSelection.getRect().x;
                                int baseY = areaItemSelection.getRect().y;
                                // kiem tra xem co click vao mui ten trai hay phai khong
                                if(e.button.x >= arrowLeft.getRect().x && e.button.x <= arrowLeft.getRect().x + arrowLeft.getRect().w &&
                                    e.button.y >= arrowLeft.getRect().y && e.button.y <= arrowLeft.getRect().y + arrowLeft.getRect().h){
                                    if(itemOffset > 0) itemOffset--;
                                    //cout << "Da nhan mui ten trai" << endl;
                                }
                                else if(e.button.x >= arrowRight.getRect().x && e.button.x <= arrowRight.getRect().x + arrowRight.getRect().w &&
                                        e.button.y >= arrowRight.getRect().y && e.button.y <= arrowRight.getRect().y + arrowRight.getRect().h){
                                    if(itemOffset + 5 < RICE && displayIndex != 0) itemOffset++;
                                    //cout << "Da nhan mui ten phai" << endl;
                                }
                                else{
                                    // Duyet qua cac icon hien thi de kiem tra click
                                    displayIndex = 0;
                                    for (int i = itemOffset; i < RICE; i++) {
                                        if (displayIndex >= 5) break; // chi hien thi toi da 5 icon
                                        ItemType it = ItemType(i);

                                        if (tvt.getInventory().getQuantity(it) > 0) {
                                            int iconX1 = baseX + displayIndex * 64;
                                            int iconX2 = iconX1 + 64;
                                            // kiem tra xem co kich vao icon nay k
                                            if (e.button.x >= iconX1 && e.button.x <= iconX2) {
                                                current_cropTyppe = CropType(i);
                                                //cout << "Da chon " << ItemDataBase::allItems[it].ItemName << endl;
                                                break; // dung khi da chon item
                                            }
                                            displayIndex++;
                                        }
                                    }
                                }
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
                            bool check = tvt.getInventory().click(e.button.x, e.button.y, tvt.getMoney());
                            if(!check) tvt.updateStage(farm); 
                        } 
                        else if(tvt.getStage() == market){
                            bool check = Market_.click(e.button.x, e.button.y,tvt.getInventory(), tvt.getMoney());
                            if(!check) tvt.updateStage(farm);
                        }    
                        
                    }
                    if(e.button.button == SDL_BUTTON_RIGHT){
                        //tvt.updateStage(farm);
                        current_gamestage = LOGIN;
                        saveGame(tvt, gMap_);
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
                    else if(e.key.keysym.sym == SDLK_1){
                        current_cropTyppe = CropType ::RICE_cp;;
                    }
                    else if(e.key.keysym.sym == SDLK_2){
                        current_cropTyppe = CropType ::CARROT_cp;
                    }
                    else if(e.key.keysym.sym == SDLK_3){
                        current_cropTyppe = CropType ::CORN_cp;
                    }
                }
            }
            else if(current_gamestage == LOGIN){
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    if(e.button.button == SDL_BUTTON_LEFT){
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;
                        //kiem tra co chon o nay khong
                        // usernameBox.setActive(usernameBox.checkClick(mouseX, mouseY));
                        // passwordBox.setActive(passwordBox.checkClick(mouseX, mouseY));
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
                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_SPACE){
                        // cout << "Username: " << usernameBox.getText() << endl;
                        // cout << "Password: " << passwordBox.getText() << endl;
                    }
                    // else if(e.key.keysym.sym == SDLK_z){
                    //     LoadGame(tvt, gMap_);
                    // }
                    // else if(e.key.keysym.sym == SDLK_l){
                    //     int userID = accountManager.login(usernameBox.getText(), passwordBox.getText());
                    //     if(userID != -1){
                    //         tvt.getID() = userID;
                    //         LoadGame(tvt, gMap_);
                    //         current_gamestage = PLAYING;
                    //     }
                    //     else{
                    //         cout << "Dang nhap that bai! Vui long kiem tra lai tai khoan." << endl;
                    //     }
                    //     usernameBox.clearText(); usernameBox.setActive(false);
                    //     passwordBox.clearText(); passwordBox.setActive(false);
                    // }
                    // else if(e.key.keysym.sym == SDLK_r){
                    //     bool success = accountManager.registerAccount(usernameBox.getText(), passwordBox.getText());
                    //     if(success){
                    //         cout << "Dang ky thanh cong! Ban co the dang nhap bang tai khoan vua tao." << endl;
                    //     }
                    //     else{
                    //         cout << "Dang ky that bai! Tai khoan da ton tai." << endl;
                    //     }
                    //     usernameBox.clearText(); usernameBox.setActive(false);
                    //     passwordBox.clearText(); passwordBox.setActive(false);
                    // }
                }
                //xu ly van ban
                // usernameBox.handleEvent(e);
                // passwordBox.handleEvent(e);
                loginInterface.getUsernameBox().handleEvent(e);
                loginInterface.getPasswordBox().handleEvent(e);
            }
        }

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

            ///
            icon_inv.render(renderer);
            icon_market.render(renderer);

            //
            if(tvt.getStage() == farm){
                // ve vung chon giong cay
                areaItemSelection.FillRect(renderer, gray);
                areaItemSelection.drawRect(renderer, black); 
                arrowLeft.render(renderer);
                arrowRight.render(renderer);
                int x_icon = 128;
                int y_icon = screen_height - 100;

                displayIndex = 0;
                for(int i = itemOffset; i < RICE && displayIndex < 5; i++){
                    ItemType it = ItemType(i);
                    if(tvt.getInventory().getQuantity(it) > 0){
                        // highlight neu dc chon
                        if(CropType(i) == current_cropTyppe){
                            Texture highlight;
                            highlight.setRect(x_icon, y_icon, 64, 94);
                            highlight.FillRect(renderer, orange);
                            highlight.drawRect(renderer, black);
                        }

                        // ve icon
                        ItemDataBase::allItems[it].icon.setRect(x_icon, y_icon, 64, 64);
                        ItemDataBase::allItems[it].icon.render(renderer);

                        // ve so luong
                        Texture qtyText;
                        string qty = "x" + to_string(tvt.getInventory().getQuantity(it));
                        qtyText.write(renderer, font, qty, black);
                        qtyText.setRect(x_icon + 32 - (qty.size()*12)/2, y_icon + 70, qty.size()*12, 20);
                        qtyText.render(renderer);

                        x_icon += 64;
                        displayIndex++;
                    }
                }
            }

            //
            if(tvt.getStage() == inventory){
                tvt.getInventory().render(renderer, font);
            }
            if(tvt.getStage() == market){
                Market_.render(renderer, font);
            }
        }
        else if(current_gamestage == LOGIN){
            // login_bg.render(renderer);
            // login_box.render(renderer);

            // login_button.FillRect(renderer, (login_button_hover)? green : gray);
            // login_button.drawRect(renderer, black);
            // login_button.render(renderer);
            // register_button.FillRect(renderer, (login_button_hover)? gray : green);
            // register_button.drawRect(renderer, black);
            // register_button.render(renderer);
            // enter_button.FillRect(renderer, (usernameBox.getText() != "" && passwordBox.getText() != "") ? green : gray);
            // enter_button.drawRect(renderer, black);
            // enter_button.render(renderer);

            // usernameBox.render(renderer, font);
            // passwordBox.render(renderer, font);
            loginInterface.render(renderer, font);
        }
        

        SDL_RenderPresent(renderer);

        endTime = SDL_GetTicks();
        TotalTime = endTime - startTime;
        //cout << TotalTime <<endl;
        //SDL_Delay((40 - TotalTime > 0)?40 - TotalTime: 0);
        
    }

    //save game
    saveGame(tvt, gMap_);

     //SDL_StopTextInput();
    TTF_CloseFont(font);
    font = NULL;
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;
}