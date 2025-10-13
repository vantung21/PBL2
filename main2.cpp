#include "Item.h"
#include "Inventory.h"


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


    ItemDataBase::init(renderer);
    Inventory inventory;
    inventory.addItem(RICE, 2);
    inventory.addItem(CARROT, 2);
    inventory.addItem(CORN, 2);
    inventory.addItem(RICE_SEED, 2);

    bool running = true;
    SDL_Event e;
    while(running){
        Uint32 startTime = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_z){

                }
            }
        }

        inventory.render(renderer);
        SDL_RenderPresent(renderer);

        Uint32 endTime = SDL_GetTicks();
        Uint32 TotalTime = endTime - startTime;
        cout << TotalTime <<endl;
        SDL_Delay(40 - TotalTime);
    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;
}