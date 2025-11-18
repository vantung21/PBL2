#include "Tutorial.h"

Tutorial::Tutorial(SDL_Renderer* renderer, TTF_Font* font){
    t_x = screen_width/8;
    t_y = screen_height/8;
    t_h = screen_height*6/8;
    t_w = screen_width*6/8;
    is_crop = true;
    cur_crop = cur_guide = 0;
    BG.Loadfromfile(renderer, "image_game/tutorial_bg.png");
    BG.setRect(t_x, t_y, t_w, t_h);
    cropTx.write(renderer, font, " Crop ", black);
    cropTx.setRect(screen_width/2 - 205, t_y + 20, 200, 50);
    guideTx.write(renderer, font, " Guide ", black);
    guideTx.setRect(screen_width/2 + 5, t_y + 20, 200, 50);

    string path = "image_game/Crop/";
    for(int i = 0; i < number_crop; i++){
        crop[i].Loadfromfile(renderer, path + to_string(i) + ".png");
        crop[i].setRect(t_x + 20, t_y + 80, t_w - 40, t_h - 130);
    }
    path = "image_game/Guide/";
    for(int i = 0; i < number_guide; i++){
        guide[i].Loadfromfile(renderer, path + to_string(i) + ".png");
        guide[i].setRect(t_x + 20, t_y + 80, t_w - 40, t_h - 130);
    }

    arrow_right.Loadfromfile(renderer, "image_game/arrow_right.png");
    arrow_right.setRect(screen_width/2 + 50, t_y + t_h - 50, 100, 35);
    arrow_left.Loadfromfile(renderer, "image_game/arrow_left.png");
    arrow_left.setRect(screen_width/2 - 150, t_y + t_h - 50, 100, 35);
}

void Tutorial::render(SDL_Renderer* renderer){
    BG.render(renderer);
    BG.drawRect(renderer, black);

    cropTx.FillRect(renderer, (is_crop)? green : gray);
    guideTx.FillRect(renderer, (!is_crop)? green : gray);
    cropTx.render(renderer);
    cropTx.drawRect(renderer, black);
    guideTx.render(renderer);
    guideTx.drawRect(renderer, black);
    if(is_crop){
        crop[cur_crop].render(renderer);
    }
    else{
        guide[cur_guide].render(renderer);
    }
    arrow_right.render(renderer);
    arrow_left.render(renderer);

}

bool Tutorial::click(int mouseX, int mouseY, Mix_Chunk* sound){
    if(cropTx.checkClickTexture(mouseX, mouseY, sound)){
        is_crop = true;
    }
    if(guideTx.checkClickTexture(mouseX, mouseY, sound)){
        is_crop = false;
    }

    if(arrow_right.checkClickTexture(mouseX, mouseY, sound)){
        if(is_crop){
            cur_crop++;
            if(cur_crop >= number_crop){
                cur_crop = 0;
            }
        }
        else {
            cur_guide++;
            if(cur_guide >= number_guide){
                cur_guide = 0;
            }
        }
    }

    if(arrow_left.checkClickTexture(mouseX, mouseY, sound)){
        if(is_crop){
            cur_crop--;
            if(cur_crop < 0){
                cur_crop = number_crop - 1;
            }
        }
        else {
            cur_guide++;
            if(cur_guide < 0){
                cur_guide = number_guide -1;
            }
        }
    }

    if(mouseX < t_x || mouseX > t_x + t_w || mouseY < t_y || mouseY > t_y + t_h){
        out();
        return false;
    }

    return true;
}

void Tutorial::out(){
    is_crop = true;
    cur_crop = 0;
    cur_guide = 0;
}