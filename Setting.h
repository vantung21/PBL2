#ifndef SETTING_H
#define SETTING_H

#include "player.h"
#include "TextBox.h"

class Setting{
    private:
        Texture settingBG, tille, line, id, username, name, renameOK, currentVL, volumeText, lineVolume, congVolume, truVolume, logOut, savegame;
        TextBox renameTextBox;
        int st_x, st_y, st_height, st_wight;
        int volumeMusic;
        bool isRenameOK;
        int saved;
    public:
        Setting(SDL_Renderer* renderer, TTF_Font* font);
        TextBox& get_renameTextBox();
        bool checkOutSetting(int x, int y);
        bool checkRenameOK(int x, int y);
        void set_isRenameOK(bool);
        void xulyRename(Player& tvt, SDL_Renderer* renderer, TTF_Font* font);
        bool xulyAmThanh(int x, int y);
        int getVolume() { return volumeMusic; }
        bool checkLogOut(int x, int y);
        bool checkSaveGame(int x, int y);
        void render(SDL_Renderer* renderer, TTF_Font* font);
        void reLoadAccountSetting(Player& tvt, SDL_Renderer *renderer, TTF_Font* font,  string strUsername);
};

#endif