#include "Rain.h"

Rain::Rain(SDL_Renderer* renderer){
    loop = 2;
    stage = 0;
    currTime = 0;
    isRaining = false;

    rainTexture[0][0][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[0][1][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[0][2][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[1][0][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[1][1][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[1][2][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[2][0][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[2][1][0].Loadfromfile(renderer, "image_game/rain_1.png");
    rainTexture[2][2][0].Loadfromfile(renderer, "image_game/rain_1.png");

    rainTexture[0][0][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[0][1][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[0][2][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[1][0][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[1][1][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[1][2][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[2][0][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[2][1][1].Loadfromfile(renderer, "image_game/rain_2.png");
    rainTexture[2][2][1].Loadfromfile(renderer, "image_game/rain_2.png");

    rainTexture[0][0][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[0][1][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[0][2][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[1][0][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[1][1][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[1][2][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[2][0][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[2][1][2].Loadfromfile(renderer, "image_game/rain_3.png");
    rainTexture[2][2][2].Loadfromfile(renderer, "image_game/rain_3.png");

    //setRect
    rainTexture[0][0][0].setRect(0,0,screen_width/3, screen_height/3);
    rainTexture[0][1][0].setRect(screen_width/3, 0, screen_width/3, screen_height/3);
    rainTexture[0][2][0].setRect(screen_width*2/3, 0, screen_width/3, screen_height/3);
    rainTexture[1][0][0].setRect(0 ,screen_height/3 , screen_width/3, screen_height/3);
    rainTexture[1][1][0].setRect(screen_width/3,screen_height/3,screen_width/3, screen_height/3);
    rainTexture[1][2][0].setRect(screen_width*2/3, screen_height/3, screen_width/3, screen_height/3);
    rainTexture[2][0][0].setRect(0, screen_height*2/3, screen_width/3, screen_height/3);
    rainTexture[2][1][0].setRect(screen_width/3, screen_height*2/3, screen_width/3, screen_height/3);
    rainTexture[2][2][0].setRect(screen_width*2/3, screen_height*2/3, screen_width/3, screen_height/3);


    rainTexture[0][0][1].setRect(0,0,screen_width/3, screen_height/3);
    rainTexture[0][1][1].setRect(screen_width/3, 0, screen_width/3, screen_height/3);
    rainTexture[0][2][1].setRect(screen_width*2/3, 0, screen_width/3, screen_height/3);
    rainTexture[1][0][1].setRect(0 ,screen_height/3 , screen_width/3, screen_height/3);
    rainTexture[1][1][1].setRect(screen_width/3,screen_height/3,screen_width/3, screen_height/3);
    rainTexture[1][2][1].setRect(screen_width*2/3, screen_height/3, screen_width/3, screen_height/3);
    rainTexture[2][0][1].setRect(0, screen_height*2/3, screen_width/3, screen_height/3);
    rainTexture[2][1][1].setRect(screen_width/3, screen_height*2/3, screen_width/3, screen_height/3);
    rainTexture[2][2][1].setRect(screen_width*2/3, screen_height*2/3, screen_width/3, screen_height/3);

    rainTexture[0][0][2].setRect(0,0,screen_width/3, screen_height/3);
    rainTexture[0][1][2].setRect(screen_width/3, 0, screen_width/3, screen_height/3);
    rainTexture[0][2][2].setRect(screen_width*2/3, 0, screen_width/3, screen_height/3);
    rainTexture[1][0][2].setRect(0 ,screen_height/3 , screen_width/3, screen_height/3);
    rainTexture[1][1][2].setRect(screen_width/3,screen_height/3,screen_width/3, screen_height/3);
    rainTexture[1][2][2].setRect(screen_width*2/3, screen_height/3, screen_width/3, screen_height/3);
    rainTexture[2][0][2].setRect(0, screen_height*2/3, screen_width/3, screen_height/3);
    rainTexture[2][1][2].setRect(screen_width/3, screen_height*2/3, screen_width/3, screen_height/3);
    rainTexture[2][2][2].setRect(screen_width*2/3, screen_height*2/3, screen_width/3, screen_height/3);


}


void Rain::execute(SDL_Renderer* renderer){
    for(int i = 0; i < 3;  i++){
        for(int j = 0; j < 3; j++){
            rainTexture[i][j][stage].render(renderer);
        }
    }
    loop--;
    if(loop <= 0){
        loop = 2;
        stage++;
        if(stage >=3){
            stage = 0;
        }
    }
}

void Rain::updateTime(int time){
    currTime += time;
    if(currTime >= timeEvent){
        loop = 2;
        stage = 0;
        currTime = 0;
        isRaining = false;
    }
}
void Rain::setIsRaining(bool raining){
    isRaining = raining;
}
bool Rain::getIsRaining(){
    return isRaining;
}

void Rain::resetCurrTime(){
    currTime = 0;
}