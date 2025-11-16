#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H
#include "TextBox.h"

class Login_Interface {
    private:
        Texture login_bg;
        Texture login_box;
        Texture login_button;
        Texture register_button;
        Texture enter_button;
        Texture note;
        Texture close_eye, open_eye;
        bool login_button_hover;

        TextBox usernameBox;
        TextBox passwordBox;
    public:
        Login_Interface( SDL_Renderer* renderer, TTF_Font* font);
        void render(SDL_Renderer* renderer, TTF_Font* font);
        bool checkClick(int x, int y, Mix_Chunk* sound = NULL);
        bool getLoginButtonHover() const { return login_button_hover; }
        TextBox& getUsernameBox();
        TextBox& getPasswordBox();
        void write_note(SDL_Renderer* renderer, TTF_Font* font, string text);
};


#endif