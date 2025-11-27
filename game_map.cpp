#include "game_map.h"
GameMap::GameMap(){
    for(int i = 0; i < max_map_y ; i++){
        for(int j =0 ; j < max_map_x; j++){
            game_map.farmland[i][j] = NULL;
        }
    }
}
GameMap::~GameMap(){
    for(int i = 0; i < max_map_y ; i++){
        for(int j =0 ; j < max_map_x; j++){
            if(game_map.farmland[i][j] != NULL)
                delete game_map.farmland[i][j];
        }
    }
}

void GameMap :: LoadMap(string name){
    ifstream file(name.c_str());   
    if(!file.is_open()){
        cout << "loi ko the mo file!\n";
        return ;
    }
    for(int i =0; i<max_map_y; i++){
        for(int j = 0; j< max_map_x; j++){
            file >> game_map.tile[i][j];
           // game_map.stages[i][j] = 0;
        }
    }
    file.close();
    game_map.file_name = name;
}

void GameMap :: LoadTiles(SDL_Renderer* renderer){
    for(int i =0; i<max_tiles; i++){
        string str1 = "image_game/";
        string str2 = to_string(i);
        string str3 = ".png";
        str1 += str2 +str3;

        ifstream fn(str1.c_str());
        if(!fn.is_open()){
            continue;
        }
        fn.close();
        tile_mat[i].Loadfromfile(renderer, str1);
    }
}

void GameMap :: DrawMap(SDL_Renderer* renderer, int root_map_x, int root_map_y){
    for(int i = 0; i< (max_map_y + 0)*tile_size; i+= tile_size){
        for(int j = 0; j < (max_map_x + 0)*tile_size; j +=tile_size){
            int val = game_map.tile[i/tile_size][j/tile_size];
            tile_mat[val].setRect(j + root_map_x, i + root_map_y, tile_size, tile_size);
            tile_mat[val].render(renderer);
        }
    }
} 

void GameMap :: save(ofstream &saveFile){
    saveFile << Crop::count << endl;
    //save farmland
    for(int i =0; i<max_map_y; i++){
        for(int j = 0; j< max_map_x; j++){
            if(game_map.farmland[i][j] != NULL){
                saveFile << i << " " << j << " " << game_map.farmland[i][j]->getType() << " " 
                         << game_map.farmland[i][j]->getGrowthStage() << " "
                         << game_map.farmland[i][j]->getGrowthTimer() << endl;
            }
        }
    }
    saveFile << -1 << endl; //dau hieu ket thuc danh sach
}

void GameMap :: clear(){
    for(int i = 0; i < max_map_y ; i++){
        for(int j =0 ; j < max_map_x; j++){
            if(game_map.farmland[i][j] != NULL){
                delete game_map.farmland[i][j];
                game_map.farmland[i][j] = NULL;
            }
        }
    }
}

