#include "Setting.h"

Setting::Setting(SDL_Renderer* renderer, TTF_Font* font) 
    : renameTextBox("Rename", screen_width/6 + 50, screen_height/6 + 300, 400, 50, FILL)
{
    st_x = screen_width/6;
    st_y = screen_height/6;
    st_wight = screen_width*4/6;
    st_height = screen_height*4/6;

    saved = 0;

    volumeMusic = 32;

    isRenameOK = false;

    settingBG.Loadfromfile(renderer, "image_game/BG_Inventory2.png");
    settingBG.setRect(st_x, st_y, st_wight, st_height);

    tille.write(renderer, font, "SETTING", black);
    int len = tille.getRect().w*70/tille.getRect().h;
    tille.setRect(st_x + st_wight/2 - len/2, st_y + 30, len , 70);

    line.setRect(tille.getRect().x - 30, tille.getRect().y + tille.getRect().h + 6, tille.getRect().w + 60, 4);

    id.write(renderer, font, "ID: 100000", black);
    len = id.getRect().w*50/id.getRect().h;
    id.setRect(st_x + 50, line.getRect().y + 30, len, 50);

    username.write(renderer, font, "Username: ", black);
    len = username.getRect().w*50/username.getRect().h;
    username.setRect(id.getRect(). x + id.getRect().w + 100, line.getRect().y + 30, len, 50);

    name.write(renderer, font, "Name: player", black);
    len = name.getRect().w*50/name.getRect().h;
    name.setRect(id.getRect().x , id.getRect().y + id.getRect().h + 30, len, 50);

    renameOK.write(renderer, font, "OK", black);
    renameOK.setRect(screen_width/6 + 50 + 450, screen_height/6 + 300, 50, 50);

    volumeText.write(renderer, font, "Volume: ", black);
    len = volumeText.getRect().w*50/volumeText.getRect().h;
    volumeText.setRect(id.getRect().x , renameOK.getRect().y + renameOK.getRect().h + 30, len, 50);

    truVolume.write(renderer, font, "-", red);
    truVolume.setRect(volumeText.getRect().x + volumeText.getRect().w + 50, volumeText.getRect().y + 10, 30, 30);

    lineVolume.setRect(volumeText.getRect().x + volumeText.getRect().w + 50 + 60, volumeText.getRect().y + 20, 128*2, 10);

    currentVL.setRect(lineVolume.getRect().x + volumeMusic*2, volumeText.getRect().y + 10, 5, 30);
    
    congVolume.write(renderer, font, "+", red);
    congVolume.setRect(lineVolume.getRect().x + lineVolume.getRect().w + 30, volumeText.getRect().y + 10, 30, 30);
    
    savegame.write(renderer, font, " Save ", black);
    len = savegame.getRect().w*50/savegame.getRect().h;
    savegame.setRect(st_x + st_wight/2 - len - 20, volumeText.getRect().y + volumeText.getRect().h + 30, len, 50);

    logOut.write(renderer, font, "Log Out", black);
    len = logOut.getRect().w*50/logOut.getRect().h;
    logOut.setRect(st_x + st_wight/2 + 20, volumeText.getRect().y + volumeText.getRect().h + 30, len, 50);
}

bool Setting::checkOutSetting(int x, int y){
    return (x < st_x || x > st_x + st_wight || y < st_y || y > st_y + st_height);
}

TextBox& Setting::get_renameTextBox(){
    return renameTextBox;
}

bool Setting::checkRenameOK(int x, int y){
    return (x >= renameOK.getRect().x && x <= renameOK.getRect().x + renameOK.getRect().w &&
             y >= renameOK.getRect().y && y <= renameOK.getRect().y + renameOK.getRect().h);
}

void Setting::xulyRename(Player& tvt, SDL_Renderer* renderer, TTF_Font* font){
    if(renameTextBox.getText() != ""){
        tvt.getname() = renameTextBox.getText();
        
        string temp = "Name: " + renameTextBox.getText();
        name.write(renderer, font, temp, black);
        int len = name.getRect().w*50/name.getRect().h;
        name.setRect(id.getRect().x , id.getRect().y + id.getRect().h + 30, len, 50);

        renameTextBox.clearText();
    }
}

void Setting::set_isRenameOK(bool ok){
    isRenameOK = ok;
}

bool Setting::xulyAmThanh(int x, int y){
    if(x >= congVolume.getRect().x && x <= congVolume.getRect().x + congVolume.getRect().w &&
        y >= congVolume.getRect().y && y <= congVolume.getRect().y + congVolume.getRect().h){
            volumeMusic += 4;
            if(volumeMusic > 128){
                volumeMusic = 128;
            }
            currentVL.setRect(lineVolume.getRect().x + volumeMusic*2, volumeText.getRect().y + 10, 5, 30);
            return true;
    }

    if(x >= truVolume.getRect().x && x <= truVolume.getRect().x + truVolume.getRect().w &&
        y >= truVolume.getRect().y && y <= truVolume.getRect().y + truVolume.getRect().h){
            volumeMusic -= 4;
            if(volumeMusic < 0){
                volumeMusic = 0;
            }
            currentVL.setRect(lineVolume.getRect().x + volumeMusic*2, volumeText.getRect().y + 10, 5, 30);
            return true;
    }
    return false;
}

bool Setting::checkLogOut(int x, int y){
    return (x >= logOut.getRect().x && x <= logOut.getRect().x + logOut.getRect().w &&
            y >= logOut.getRect().y && y <= logOut.getRect().y + logOut.getRect().h);
}

bool Setting::checkSaveGame(int x, int y){
    if(x >= savegame.getRect().x && x <= savegame.getRect().x + savegame.getRect().w &&
            y >= savegame.getRect().y && y <= savegame.getRect().y + savegame.getRect().h){
                saved = 10;
                return true;
    }
    return false;
}

void Setting::reLoadAccountSetting(Player& tvt, SDL_Renderer *renderer, TTF_Font* font, string strUsername){
    string temp = "ID: " + to_string(tvt.getID());
    id.write(renderer, font, temp, black);
    int len = id.getRect().w*50/id.getRect().h;
    id.setRect(st_x + 50, line.getRect().y + 30, len, 50);

    temp = "Username: " + strUsername;
    username.write(renderer, font, temp, black);
    len = username.getRect().w*50/username.getRect().h;
    username.setRect(id.getRect(). x + id.getRect().w + 100, line.getRect().y + 30, len, 50);

    temp = "Name: " + tvt.getname();
    name.write(renderer, font, temp, black);
    len = name.getRect().w*50/name.getRect().h;
    name.setRect(id.getRect().x , id.getRect().y + id.getRect().h + 30, len, 50);
}

void Setting::render(SDL_Renderer* renderer, TTF_Font* font){
    settingBG.render(renderer);
    tille.render(renderer);
    line.FillRect(renderer, black);

    id.render(renderer);
    username.render(renderer);

    name.render(renderer);

    renameOK.FillRect(renderer, isRenameOK? green : gray);
    renameOK.drawRect(renderer, black);
    renameOK.render(renderer);

    volumeText.render(renderer); 

    lineVolume.FillRect(renderer, black); 

    currentVL.FillRect(renderer, red);

    congVolume.FillRect(renderer, gray);
    congVolume.drawRect(renderer, black);
    congVolume.render(renderer);

    truVolume.FillRect(renderer, gray);
    truVolume.drawRect(renderer, black);
    truVolume.render(renderer); 

    logOut.FillRect(renderer, orange);
    logOut.drawRect(renderer, black);
    logOut.render(renderer);

    if(saved > 0){
        savegame.FillRect(renderer, green);
        saved--;
    }
    else savegame.FillRect(renderer, orange);
    savegame.drawRect(renderer, black);
    savegame.render(renderer);

    renameTextBox.render(renderer, font);
}

void Setting::out(){
    renameTextBox.clearText();
    renameTextBox.setActive(false);
}
