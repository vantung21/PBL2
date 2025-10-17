#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "include.h"
#include "Texture.h"
#include "crop.h"

#define max_tiles 50

struct Map{
    int tile[max_map_y][max_map_x];
    //int stages[max_map_y][max_map_x];
    Crop* farmland[max_map_y][max_map_x];
    string file_name;
};

class TileMat : public Texture{
    public:
        TileMat() {;}
        ~TileMat() {;}
};


class GameMap{
    private:
        Map game_map;
        TileMat tile_mat[max_tiles];
    public:
        GameMap();
        ~GameMap();
        void LoadMap(string name);
        void LoadTiles(SDL_Renderer* renderer);
        void DrawMap(SDL_Renderer* renderer);
        Map& getMap() { return game_map; }
        void update(int, int);
        void save(ofstream &saveFile);
        void clear();
};

#endif