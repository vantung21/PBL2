#include "Game.h"

SDL_Window* Game::window = NULL;
SDL_Renderer* Game::renderer = NULL;
TTF_Font* Game::font = NULL;

bool Game::initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_StartTextInput();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    window = SDL_CreateWindow("MY FARM", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 
                              screen_width, 
                              screen_height, 
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("font.ttf", 32);

    return (window && renderer && font);
}

Game::Game()
    : running(true), windowActive(true),
      current_gameStage(LOGIN),
      player_(renderer,font), market_(renderer, font),
      setting_(renderer, font), tutorial_(renderer, font),
      shovel_(renderer), water_(renderer, font),
      loginUI(renderer, font),
      choosen_seed(renderer),
      rain_(renderer),
      current_cropType(RICE_cp)
{
    loadResources();
}

Game::~Game() {
    saveGame();
    quitSDL();
}


void Game::loadResources() {
    // music
    music_game = Mix_LoadMUS("sound/farm_theme.mp3");
    if (music_game) {
        Mix_VolumeMusic(32);
        Mix_PlayMusic(music_game, -1);
    }

    buttonSound = Mix_LoadWAV("sound/button.wav");
    trongcaySound = Mix_LoadWAV("sound/trongcay.wav");
    thuhoachSound = Mix_LoadWAV("sound/thuhoach.wav");
    leveupSound = Mix_LoadWAV("sound/levelup.wav");
    openDoorSound = Mix_LoadWAV("sound/opening_door.wav");
    tingTingSound = Mix_LoadWAV("sound/tingting.wav");
    shovelSound = Mix_LoadWAV("sound/shovel.wav");
    wateringSound = Mix_LoadWAV("sound/watering.wav");

    // map
    gameMap_.LoadMap("newmap.txt");
    gameMap_.LoadTiles(renderer);

    loadIcons();

    // crop database
    CropManager::init(renderer);
    Crop::loadBlingBling(renderer);

    ItemDataBase::init(renderer);
}

void Game::loadIcons() {
    house.Loadfromfile(renderer, "image_game/House.png");
    house.setRect(tile_size, tile_size, tile_size*5, tile_size*7);

    icon_inv.Loadfromfile(renderer, "image_game/Icon_Inventory.png");
    icon_inv.setRect(screen_width - 70, screen_height - 70, 64, 64);

    icon_market.Loadfromfile(renderer, "image_game/Icon_Shop.png");
    icon_market.setRect(screen_width - 70, screen_height - 140, 64, 64);

    icon_setting.Loadfromfile(renderer, "image_game/Icon_Setting.png");
    icon_setting.setRect(screen_width - 70, screen_height - 210, 64, 64);

    icon_tutorial.Loadfromfile(renderer, "image_game/Icon_tutorial.png");
    icon_tutorial.setRect(screen_width - 70, screen_height - 280, 64, 64);
}

void Game::run() {
    SDL_Event e;
    Uint32 startTime, endTime, TotalTime;

    while (running) {
        startTime = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
            else if(e.type == SDL_WINDOWEVENT){
                if(e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED){
                    windowActive = true;
                    cout << "Window focused." << endl;
                    Mix_ResumeMusic();
                }
                else if(e.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
                    windowActive = false;
                    cout << "Window unfocused." << endl;
                    Mix_PauseMusic();
                }
            }

            if (current_gameStage == LOGIN)
                handleLoginEvents(e);
            else if(current_gameStage == PLAYING)
                handlePlayingEvents(e);
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    running = false;
                }
            }
        }
        if (!running) break;
        update();
        if(windowActive) render();
        endTime = SDL_GetTicks();
        TotalTime = endTime - startTime;
        if (TotalTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - TotalTime);
        }
    }
}

void Game::handleLoginEvents(SDL_Event& e) {
    // ---- toàn bộ block LOGIN trong main ----
    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button == SDL_BUTTON_LEFT){
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            //kiem tra co chon o nay khong
            loginUI.getUsernameBox().setActive(loginUI.getUsernameBox().checkClick(mouseX, mouseY));
            loginUI.getPasswordBox().setActive(loginUI.getPasswordBox().checkClick(mouseX, mouseY));
            //kiem tra co bam nut login/register/enter khong
            if(loginUI.checkClick(mouseX, mouseY, buttonSound)){
                if(loginUI.getLoginButtonHover()){
                    //login
                    int userID = accountManager.login(loginUI.getUsernameBox().getText(), loginUI.getPasswordBox().getText());
                    if(userID != -1){
                        player_.getID() = userID;
                        loadGame();
                        setting_.reLoadAccountSetting(player_, renderer, font, loginUI.getUsernameBox().getText());
                        loginUI.write_note(renderer, font, " ");
                        current_gameStage = PLAYING;
                        player_.updateStage(farm);
                        player_.update_moneyTexture(renderer, font);
                        player_.update_nameText(renderer, font);
                        player_.updateExp(renderer, font, rain_, 0);
                    }
                    else{
                        //cout << "Dang nhap that bai! Vui long kiem tra lai tai khoan." << endl;
                        if(loginUI.getUsernameBox().getText() != "" && loginUI.getPasswordBox().getText() != ""){
                            loginUI.write_note(renderer, font, "Login failed! Please check your account again.");
                        }
                    }
                    loginUI.getUsernameBox().clearText(); loginUI.getUsernameBox().setActive(false);
                    loginUI.getPasswordBox().clearText(); loginUI.getPasswordBox().setActive(false);
                }
                else{
                    //register
                    bool success = accountManager.registerAccount(loginUI.getUsernameBox().getText(), loginUI.getPasswordBox().getText());
                    if(success){
                        //cout << "Dang ky thanh cong! Ban co the dang nhap bang tai khoan vua tao." << endl;
                        loginUI.write_note(renderer, font, "Registration successful!");
                    }
                    else{
                        //cout << "Dang ky that bai! Tai khoan da ton tai." << endl;
                        if(loginUI.getUsernameBox().getText() != "" && loginUI.getPasswordBox().getText() != ""){
                            loginUI.write_note(renderer, font, "Registration failed! The account already exists.");
                        }
                    }
                }
            }
        }
        else if(e.button.button == SDL_BUTTON_RIGHT){
            current_gameStage = PLAYING;
        }
    }
    else if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_RETURN){
            Mix_PlayChannel(-1, buttonSound, 0);
            if(loginUI.getLoginButtonHover()){
                //login
                int userID = accountManager.login(loginUI.getUsernameBox().getText(), loginUI.getPasswordBox().getText());
                if(userID != -1){
                    player_.getID() = userID;
                    loadGame();
                    setting_.reLoadAccountSetting(player_, renderer, font, loginUI.getUsernameBox().getText());
                    loginUI.write_note(renderer, font, " ");
                    current_gameStage = PLAYING;
                    player_.updateStage(farm);
                    player_.update_moneyTexture(renderer, font);
                    player_.update_nameText(renderer, font);
                    player_.updateExp(renderer, font, rain_, 0);
                }
                else{
                    //cout << "Dang nhap that bai! Vui long kiem tra lai tai khoan." << endl;
                    if(loginUI.getUsernameBox().getText() != "" && loginUI.getPasswordBox().getText() != ""){
                        loginUI.write_note(renderer, font, "Login failed! Please check your account again.");
                    }
                }
                loginUI.getUsernameBox().clearText(); loginUI.getUsernameBox().setActive(false);
                loginUI.getPasswordBox().clearText(); loginUI.getPasswordBox().setActive(false);
            }
            else{
                //register
                bool success = accountManager.registerAccount(loginUI.getUsernameBox().getText(), loginUI.getPasswordBox().getText());
                if(success){
                    //cout << "Dang ky thanh cong! Ban co the dang nhap bang tai khoan vua tao." << endl;
                    loginUI.write_note(renderer, font, "Registration successful!");
                }
                else{
                    //cout << "Dang ky that bai! Tai khoan da ton tai." << endl;
                    if(loginUI.getUsernameBox().getText() != "" && loginUI.getPasswordBox().getText() != ""){
                        loginUI.write_note(renderer, font, "Registration failed! The account already exists.");
                    }
                }
            }
        }
    }

    //xu ly van ban
    loginUI.getUsernameBox().handleEvent(e);
    loginUI.getPasswordBox().handleEvent(e);
}

void Game::handlePlayingEvents(SDL_Event& e) {
    // ---- toàn bộ block PLAYING trong main ----
    int random = 0;
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        int x = (mouseX - root_map_x)/tile_size;
        int y = (mouseY - root_map_y)/tile_size;

        if(e.button.button == SDL_BUTTON_LEFT){
            if(player_.getStage() == farm){
                if(icon_inv.checkClickTexture(mouseX, mouseY, buttonSound) || house.checkClickTexture(mouseX, mouseY, openDoorSound)){
                    player_.updateStage(inventory);
                }
                else if(icon_market.checkClickTexture(mouseX, mouseY, buttonSound)){
                    player_.updateStage(market);
                }
                else if(icon_setting.checkClickTexture(mouseX, mouseY, buttonSound)){
                    player_.updateStage(setting);
                }
                else if(icon_tutorial.checkClickTexture(mouseX, mouseY, buttonSound)){
                    player_.updateStage(tutorial);
                }
                else if(choosen_seed.checkclick(mouseX, mouseY, buttonSound)){
                    choosen_seed.xuLyClick(mouseX, mouseY, player_, current_cropType);
                }
                else if(shovel_.checkClick(mouseX, mouseY)){
                    shovel_.setHold(true);
                    player_.updateStage(shovel);
                }
                else if(water_.checkClick(mouseX, mouseY)){
                    water_.setHold(true);
                    player_.updateStage(watering);
                }
                
                else if( gameMap_.getMap().farmland[y][x] == NULL){
                    if((gameMap_.getMap().tile[y][x] >=17 && gameMap_.getMap().tile[y][x] <= 24) || (gameMap_.getMap().tile[y][x] == 3)){
                        int t = current_cropType;
                        if(current_cropType == APPLE_cp) return;
                        if(player_.getInventory().getQuantity((ItemType)t) > 0){
                            Mix_PlayChannel(-1, trongcaySound, 0);
                            Crop* newCp = new Crop(current_cropType, x*tile_size, y*tile_size);
                            gameMap_.getMap().farmland[y][x] = newCp;
                            player_.getInventory().removeItem((ItemType)t, 1);
                        }
                    }
                    else if(gameMap_.getMap().tile[y][x] == 1){
                        int t = current_cropType;
                        if(current_cropType != APPLE_cp) return;
                        if(player_.getInventory().getQuantity((ItemType)t) > 0){
                            Mix_PlayChannel(-1, trongcaySound, 0);
                            Crop* newCp = new Crop(current_cropType, x*tile_size, y*tile_size);
                            gameMap_.getMap().farmland[y][x] = newCp;
                            player_.getInventory().removeItem((ItemType)t, 1);
                        }
                    }
                }
                else if(gameMap_.getMap().farmland[y][x] != NULL ){
                    if((gameMap_.getMap().farmland[y][x])->isReadyToHarvest()){
                        Mix_PlayChannel(-1, thuhoachSound, 0);
                        random = (SDL_GetTicks()/1000)%5;
                        for(int i = 0; i < CropManager::getData(gameMap_.getMap().farmland[y][x]->getType()).harvestedItems.getSize(); i++){
                            ItemType item = CropManager::getData(gameMap_.getMap().farmland[y][x]->getType()).harvestedItems[i];
                            player_.getInventory().addItem(item, (random == 0)?3:2);
                        }
                        bool levelup = player_.updateExp(renderer, font, rain_, CropManager::getData(gameMap_.getMap().farmland[y][x]->getType()).exp);
                        if(levelup) Mix_PlayChannel(-1, leveupSound, 0);
                        if((gameMap_.getMap().farmland[y][x])->getType() == APPLE_cp){
                            gameMap_.getMap().farmland[y][x]->getGrowthStage() = 3;
                            gameMap_.getMap().farmland[y][x]->getGrowthTimer() = 0;
                            return;
                        }
                        delete gameMap_.getMap().farmland[y][x];
                        gameMap_.getMap().farmland[y][x] = NULL;
                    }
                }
            }
            else if(player_.getStage() == inventory){
                bool check = player_.getInventory().click(mouseX, mouseY, player_.getMoney(), tingTingSound, buttonSound);
                player_.update_moneyTexture(renderer, font);
                if(!check) player_.updateStage(farm); 
            } 
            else if(player_.getStage() == market){
                bool check = market_.click(mouseX, mouseY,player_.getInventory(), player_, tingTingSound, buttonSound);
                player_.update_moneyTexture(renderer, font);
                if(!check) player_.updateStage(farm);
            }  
            else if(player_.getStage() == setting){
                if(setting_.checkLogOut(mouseX, mouseY, buttonSound)) {
                    saveGame();
                    current_gameStage = LOGIN;
                }
                if(setting_.checkSaveGame(mouseX, mouseY, buttonSound)) {
                    saveGame();
                }
                if(setting_.xulyAmThanh(mouseX, mouseY, buttonSound)) {
                    Mix_VolumeMusic(setting_.getVolume());
                }
                
                setting_.get_renameTextBox().setActive(setting_.get_renameTextBox().checkClick(mouseX, mouseY));
                if(setting_.checkRenameOK(mouseX, mouseY, buttonSound)){
                    setting_.xulyRename(player_, renderer, font);
                    player_.update_nameText(renderer, font);
                }

                if(setting_.checkOutSetting(mouseX, mouseY, buttonSound)){
                    setting_.out();
                    player_.updateStage(farm);
                }
            }
            else if(player_.getStage() == tutorial){
                if(!tutorial_.click(mouseX, mouseY, buttonSound)){
                    player_.updateStage(farm);
                }
            }
            else if(player_.getStage() == shovel){
                if(shovel_.checkClick(mouseX, mouseY)){
                    shovel_.drop();
                    player_.updateStage(farm);
                }
                else if(gameMap_.getMap().farmland[y][x] != NULL){
                    Mix_PlayChannel(-1, shovelSound, 0);
                    shovel_.shoveling();
                    delete gameMap_.getMap().farmland[y][x];
                    gameMap_.getMap().farmland[y][x] = NULL;
                }
            } 
            else if(player_.getStage() == watering){
                if(water_.checkClick(mouseX, mouseY)){
                    water_.drop();
                    player_.updateStage(farm);
                }
                else if(gameMap_.getMap().farmland[y][x] != NULL){
                    if(water_.getQuantity() > 0){
                        water_.Watering();
                        Mix_PlayChannel(-1, wateringSound, 0);
                        gameMap_.getMap().farmland[y][x]->update(20000);
                    }
                }
            }
            
        }
    }
    else if(e.type == SDL_MOUSEMOTION){
        int mouseX = e.motion.x;
        int mouseY = e.motion.y;
        //kiem tra hover login button
        if(shovel_.getHold() == true){
            shovel_.setPos(mouseX, mouseY);
        }
        else if(water_.getHold() == true){
            water_.setPos(mouseX, mouseY);
        }
    }
    else if(e.type == SDL_KEYDOWN){
        if(player_.getStage() == farm || player_.getStage() == shovel || player_.getStage() == watering){
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
        bool sound = true;
        if(player_.getStage() == farm){
            if(e.key.keysym.sym == SDLK_v) {
                player_.updateStage(inventory);
            }
            else if(e.key.keysym.sym == SDLK_b) {
                player_.updateStage(market);
            }
            else if(e.key.keysym.sym == SDLK_TAB) {
                player_.updateStage(setting);
            }
            else if(e.key.keysym.sym == SDLK_c){
                player_.updateStage(tutorial);
            }
            else if(e.key.keysym.sym == SDLK_SPACE){
                choosen_seed.set_isopen(!choosen_seed.get_isopen());
            }
            else sound = false;
        }
        else if(player_.getStage() == inventory && e.key.keysym.sym == SDLK_v){
            player_.getInventory().out();
            player_.updateStage(farm);
        } 
        else if(player_.getStage() == market && e.key.keysym.sym == SDLK_b){
            market_.out();
            player_.updateStage(farm);
        } 
        else if(player_.getStage() == setting && e.key.keysym.sym == SDLK_TAB){
            setting_.out();
            player_.updateStage(farm);
        }
        else if(player_.getStage() == tutorial && e.key.keysym.sym == SDLK_c){
            tutorial_.out();
            player_.updateStage(farm);
        }
        else sound = false;
        if(sound) Mix_PlayChannel(-1, buttonSound, 0);
    }

    //
    if(player_.getStage() == setting){
        setting_.get_renameTextBox().handleEvent(e);
        if(setting_.get_renameTextBox().getText() != ""){
            setting_.set_isRenameOK(true);
        }
        else setting_.set_isRenameOK(false);
    }
}

void Game::update() {
    if (current_gameStage == PLAYING) {
        // update cây, update timer -> giống đoạn bạn đã làm
        for(int i = 0; i < max_map_y; i++){
            for(int j = 0; j < max_map_x; j++){
                if(gameMap_.getMap().farmland[i][j] != NULL){
                    gameMap_.getMap().farmland[i][j]->update(FRAME_DELAY);
                }
                if(rain_.getIsRaining()){
                    gameMap_.getMap().farmland[i][j]->update(FRAME_DELAY);
                }
            }
        }
        water_.updateQuatity(renderer, font, FRAME_DELAY);
        if(rain_.getIsRaining()){
            water_.updateQuatity(renderer, font, FRAME_DELAY);
            rain_.updateTime(FRAME_DELAY);
        }
        if(rain_.getIsRaining()){
            rain_.execute(renderer);
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (current_gameStage == LOGIN) {
        loginUI.render(renderer, font);
    }
    else {
        gameMap_.DrawMap(renderer);

        for(int i = 0; i < max_map_y ; i++){
            for(int j =0 ; j < max_map_x; j++){
                if(gameMap_.getMap().farmland[i][j] != NULL){
                    gameMap_.getMap().farmland[i][j]->render(renderer) ;
                }
            }
        }

        house.setRect(tile_size + root_map_x, tile_size + root_map_y, tile_size*5, tile_size*7);
        house.render(renderer);
        player_.render(renderer);
        water_.render(renderer);
        shovel_.render(renderer);
        if(player_.getStage() == farm) choosen_seed.render(renderer, font, player_, current_cropType);

        icon_inv.render(renderer);
        icon_market.render(renderer);
        icon_setting.render(renderer);
        icon_tutorial.render(renderer);

        // render stage đặc biệt
        if (player_.getStage() == inventory) player_.getInventory().render(renderer, font);
        if (player_.getStage() == market) market_.render(renderer, font, player_);
        if (player_.getStage() == setting) setting_.render(renderer, font);
        if (player_.getStage() == tutorial) tutorial_.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::quitSDL() {
    SDL_StopTextInput();
    TTF_CloseFont(font); font = NULL;

    Mix_FreeChunk(buttonSound);
    Mix_FreeChunk(trongcaySound);
    Mix_FreeChunk(thuhoachSound);
    Mix_FreeChunk(leveupSound);
    Mix_FreeChunk(openDoorSound);
    Mix_FreeChunk(tingTingSound);
    Mix_FreeChunk(shovelSound);
    Mix_FreeChunk(wateringSound);

    Mix_FreeMusic(music_game); music_game = NULL;

    SDL_DestroyRenderer(renderer); renderer = NULL;
    SDL_DestroyWindow(window); window = NULL;

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::saveGame() {
    string id = to_string(player_.getID());
    ofstream saveFile("savegame/" + id + ".txt");
    if(!saveFile.is_open()){
        cout << "loi! Khong the tao file save." << endl;
        return;
    }
    //save player
    saveFile << player_.getID() << endl;
    saveFile << player_.getname() << endl;
    saveFile << player_.getMoney() << endl;
    saveFile << player_.getLevel() << endl;
    saveFile << player_.getExp() << endl;
    saveFile << water_.getQuantity() << endl;
    //save inventory
    player_.getInventory().save(saveFile);
    //save map
    gameMap_.save(saveFile);

    cout << "Game da duoc luu! (ID: " << player_.getID() << ")" << endl;
}

void Game::loadGame() {
    player_.getInventory().clear();
    player_.clear();
    gameMap_.clear();
    water_.setQuantity(10);
    
    string id = to_string(player_.getID());
    ifstream loadFile("savegame/" + id + ".txt");
    if(!loadFile.is_open()){
        cout << "loi! Khong the mo file save. (ID: " << id << ")" << endl;
        player_.getInventory().addItem(RICE_SEED, 5);
        player_.getInventory().addItem(CARROT_SEED, 2);     
        return;   
    }

    //load player
    string load;
    loadFile >> load;
    player_.getID() = stoi(load);
    loadFile >> load;
    player_.getname() = load;
    loadFile >> load;
    player_.getMoney() = stoi(load);
    loadFile >> load;
    player_.getLevel() = stoi(load);
    loadFile >> load;
    player_.getExp() = stoi(load);
    loadFile >> load;
    water_.setQuantity(stoi(load));

    //load inventory
    int countType;
    loadFile >> countType;
    for(int i =0; i< countType; i++){
        int itemInt, quantity;
        loadFile >> itemInt >> quantity;
        player_.getInventory().addItem(ItemType(itemInt), quantity);
    }
    
    //load map
    int cntcrop;
    loadFile >> cntcrop;
    for(int i =0; i< cntcrop; i++){
        int x, y, typeInt, stage, timer;
        loadFile >> x >> y >> typeInt >> stage >> timer;
        Crop* newCp = new Crop(CropType(typeInt), y*tile_size, x*tile_size);
        newCp->getGrowthStage() = stage;
        newCp->getGrowthTimer() = timer;
        gameMap_.getMap().farmland[x][y] = newCp;
    }
    int end;
    loadFile >> end;
    if(end == -1){
        cout << "load game thanh cong! (ID: " << player_.getID() << ")" << endl;
    }
    else{
        cout << "load game that bai!" << endl;
    }
}
