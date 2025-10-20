#include "Login_Interface.h"

Login_Interface::Login_Interface(SDL_Renderer* renderer, TTF_Font* font) : usernameBox("Username", screen_width/2 - 200, screen_height/2 + 80, 400, 50, UNDERLINE),
                                                        passwordBox("Password", screen_width/2 -200, screen_height/2 + 150, 400, 50, UNDERLINE){
    login_bg.Loadfromfile(renderer, "image_game/LOGIN_BG.png");
    login_bg.setRect(0, 0 , screen_width, screen_height);
    
    login_box.Loadfromfile(renderer, "image_game/board_login.png");
    login_box.setRect(0, 0 , screen_width, screen_height);

    login_button.write(renderer, font, " LOGIN " , black);
    login_button.setRect(screen_width/2 -200, screen_height/2 + 10, 180, 60);

    register_button.write(renderer, font, "REGISTER" , black);
    register_button.setRect(screen_width/2 + 20, screen_height/2 + 10, 180, 60);

    login_button_hover = true;
    
    enter_button.write(renderer, font, " ENTER " , black);
    enter_button.setRect(screen_width/2 -100, screen_height/2 + 220, 200, 60);
}

TextBox& Login_Interface::getPasswordBox(){
    return passwordBox;
}
TextBox& Login_Interface::getUsernameBox(){
    return usernameBox;
}

void Login_Interface::render(SDL_Renderer* renderer, TTF_Font* font){
    login_bg.render(renderer);
    login_box.render(renderer);

    login_button.FillRect(renderer, (login_button_hover)? green : gray);
    login_button.drawRect(renderer, black);
    login_button.render(renderer);
    register_button.FillRect(renderer, (login_button_hover)? gray : green);
    register_button.drawRect(renderer, black);
    register_button.render(renderer);
    enter_button.FillRect(renderer, (usernameBox.getText() != "" && passwordBox.getText() != "") ? green : gray);
    enter_button.drawRect(renderer, black);
    enter_button.render(renderer);

    usernameBox.render(renderer, font);
    passwordBox.render(renderer, font);
}

bool Login_Interface::checkClick(int x, int y){
    if(login_button.getRect().x <= x && x <= login_button.getRect().x + login_button.getRect().w &&
       login_button.getRect().y <= y && y <= login_button.getRect().y + login_button.getRect().h){
           login_button_hover = true;
           usernameBox.clearText();
           passwordBox.clearText();
    }
    else if(register_button.getRect().x <= x && x <= register_button.getRect().x + register_button.getRect().w &&
            register_button.getRect().y <= y && y <= register_button.getRect().y + register_button.getRect().h){
                login_button_hover = false;
                usernameBox.clearText();
                passwordBox.clearText();
    }
    else if(enter_button.getRect().x <= x && x <= enter_button.getRect().x + enter_button.getRect().w &&
            enter_button.getRect().y <= y && y <= enter_button.getRect().y + enter_button.getRect().h){
                return true;
    }
    return false;
}