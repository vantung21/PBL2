#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "include.h"
#include "Texture.h"

enum typeBox{
    FILL, UNDERLINE
};

class TextBox {
private:
    Texture box;
    string text;
    string placeholder;
    bool is_active; 
    int startPos;
    typeBox boxType;

public:
    TextBox(string placeholder, int x = 0, int y = 0, int w = 50, int h = 30, typeBox boxType = UNDERLINE);

    // 1.  (Input)
    void handleEvent(SDL_Event& e);

    // 2. (Render)
    void render(SDL_Renderer* renderer, TTF_Font* font);

    // 3. Logic
    bool checkClick(int mouseX, int mouseY);
    string getText() const; 
    void setActive(bool state);
    void clearText();
};

#endif