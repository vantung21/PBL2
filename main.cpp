#include "include.h"
#include "Texture.h"
#include "game_map.h"
#include "crop.h"
#include "player.h"
#include "Market.h"

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

    Texture House;
    House.Loadfromfile(renderer, "image_game/House.png");
    House.setRect(64, 64, 64*5, 64*7);
    Texture name;

    Texture icon_inv;
    icon_inv.Loadfromfile(renderer, "image_game/Icon_Inventory.png");
    icon_inv.setRect(screen_width - 70, screen_height - 70, 64, 64);

    Texture icon_market;
    icon_market.Loadfromfile(renderer, "image_game/Icon_Shop.png");
    icon_market.setRect(screen_width - 70, screen_height - 140, 64, 64);


    name.setRect(10, 10, 100, 30);
    name.write(renderer, font, "TVT", black);
    Texture money;
    money.setRect(110, 10, 30, 30);


    // loop game
    bool invetorystart = false;
    Uint32 startTime, endTime, TotalTime;
    SDL_Event e;
    bool running = true;
    while(running){
        startTime = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            else if(e.type == SDL_MOUSEBUTTONDOWN){
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
                                tvt.getMoney() += 2;
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
                    tvt.updateStage(farm);
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // mau nen (den)
        SDL_RenderClear(renderer);

        gMap_.DrawMap(renderer);

        for(int i = 0; i < max_map_y ; i++){
            for(int j =0 ; j < max_map_x; j++){
                if(gMap_.getMap().farmland[i][j] != NULL){
                    gMap_.getMap().farmland[i][j]->update(40);
                    gMap_.getMap().farmland[i][j]->render(renderer) ;
                }
            }
        }
        name.FillRect(renderer, white);
        name.render(renderer);
        money.write(renderer, font, to_string(tvt.getMoney()), black);
        money.render(renderer);

        ///
        icon_inv.render(renderer);
        icon_market.render(renderer);

        //
        if(tvt.getStage() == inventory){
            tvt.getInventory().render(renderer, font);
        }
        if(tvt.getStage() == market){
            Market_.render(renderer, font);
        }
        

        //House.render(renderer);
        SDL_RenderPresent(renderer);

        endTime = SDL_GetTicks();
        TotalTime = endTime - startTime;
        cout << TotalTime <<endl;
        //SDL_Delay((40 - TotalTime > 0)?40 - TotalTime: 0);
        
    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;
}