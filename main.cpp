#include "include.h"
#include "Texture.h"
#include "game_map.h"
#include "crop.h"


void repo_window(){
    SDL_Window *repo = SDL_CreateWindow("REPO", SDL_WINDOWPOS_CENTERED, 
                                                    SDL_WINDOWPOS_CENTERED, 
                                                    screen_width/2, 
                                                    screen_height/2, 
                                                    SDL_WINDOW_SHOWN);
    SDL_Renderer* renderRepo = SDL_CreateRenderer(repo, -1, SDL_RENDERER_ACCELERATED);
        Texture House2;
    House2.Loadfromfile(renderRepo, "image_game/House.png");
    House2.setRect(tile_size, tile_size, tile_size*5, tile_size*7);
    
    Uint32 repoWindowID = SDL_GetWindowID(repo);
    bool run = true;
    SDL_Event eRepo;
    while(run){
        while(SDL_PollEvent(&eRepo)){
            if(eRepo.type == SDL_QUIT){
                run = false; // Đóng cửa sổ REPO
            }
            // 2. THÊM ĐOẠN NÀY VÀO: Kiểm tra sự kiện dành riêng cho cửa sổ
            else if(eRepo.type == SDL_WINDOWEVENT){
                // Chỉ xử lý nếu sự kiện này là của cửa sổ REPO
                if(eRepo.window.windowID == repoWindowID){
                    // Nếu sự kiện là yêu cầu đóng cửa sổ
                    if(eRepo.window.event == SDL_WINDOWEVENT_CLOSE){
                        run = false; // Thoát khỏi vòng lặp của cửa sổ REPO
                    }
                }
            }
            else if(eRepo.type == SDL_KEYDOWN){
                if(eRepo.key.keysym.sym == SDLK_RIGHT){
                    House2.setRect(House2.getRect().x +10, House2.getRect().y);
                }
                else if(eRepo.key.keysym.sym == SDLK_LEFT){
                    House2.setRect(House2.getRect().x -10, House2.getRect().y);
                }
                else if(eRepo.key.keysym.sym == SDLK_UP){
                    House2.setRect(House2.getRect().x, House2.getRect().y - 10);
                }
                else if(eRepo.key.keysym.sym == SDLK_DOWN){
                    House2.setRect(House2.getRect().x, House2.getRect().y + 10);
                }
            }
        }
        SDL_SetRenderDrawColor(renderRepo, 200, 100, 0, 255); // mau nen (den)
        SDL_RenderClear(renderRepo);

        House2.render(renderRepo);
        SDL_RenderPresent(renderRepo);
    }
    
    SDL_DestroyRenderer(renderRepo);
    SDL_DestroyWindow(repo);
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
    


    //crop
    CropManager :: init( renderer);
    vector<Crop> plantedCrops;
    Crop newCarrot(CARROT, 9* tile_size, 2 * tile_size); 
    plantedCrops.push_back(newCarrot);
    Crop newCarrot1(CARROT, 9* tile_size, 3 * tile_size); 
    plantedCrops.push_back(newCarrot1);


    GameMap gMap_;
    gMap_.LoadMap("newmap.txt");
    gMap_.LoadTiles(renderer);

    Texture House;
    House.Loadfromfile(renderer, "image_game/House.png");
    House.setRect(64, 64, 64*5, 64*7);

    // loop game
    SDL_Event e;
    bool running = true;
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                int x= e.button.x - root_map_x;
                int y= e.button.y - root_map_y;
                if(e.button.button == SDL_BUTTON_LEFT){     
                    x /= tile_size;
                    y /= tile_size;
                    if((gMap_.getMap().tile[y][x] >=17 && gMap_.getMap().tile[y][x] <= 24 || gMap_.getMap().tile[y][x] == 3) && gMap_.getMap().stages[y][x] == 0){
                        Crop newCp(CARROT, x*tile_size, y*tile_size);
                        plantedCrops.push_back(newCp);
                        gMap_.update(y,x);
                    }
                }
                if(e.button.button == SDL_BUTTON_RIGHT){
                    x /= tile_size;
                    y /= tile_size;
                    if((gMap_.getMap().tile[y][x] >=17 && gMap_.getMap().tile[y][x] <= 24 || gMap_.getMap().tile[y][x] == 3) && gMap_.getMap().stages[y][x] == 0){
                        Crop newCp(CORN, x*tile_size, y*tile_size);
                        plantedCrops.push_back(newCp);
                        gMap_.update(y,x);
                    }
                }
            }
            else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_s){
                    root_map_y -= tile_size/2;
                } 
                else if(e.key.keysym.sym == SDLK_w){
                    root_map_y += tile_size/2;
                }
                else if(e.key.keysym.sym == SDLK_d){
                    root_map_x -= tile_size/2;
                }
                else if(e.key.keysym.sym == SDLK_a){
                    root_map_x += tile_size/2;
                }
                else if(e.key.keysym.sym == SDLK_SPACE){
                    repo_window();
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // mau nen (den)
        SDL_RenderClear(renderer);

        gMap_.DrawMap(renderer);

        for (auto& crop : plantedCrops) {
            crop.update(1); // deltaTime là thời gian giữa 2 frame
            crop.render(renderer);
        }

        //House.render(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(40);
    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;
}