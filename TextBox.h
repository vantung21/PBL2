#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "include.h"
#include "Texture.h"

class TextBox {
private:
    Texture box;
    string text;
    bool is_active; 

public:
    TextBox(int x = 0, int y = 0, int w = 50, int h = 30); 

    // 1.  (Input)
    void handleEvent(SDL_Event& e);

    // 2. (Render)
    void render(SDL_Renderer* renderer, TTF_Font* font);

    // 3. Logic
    bool checkClick(int mouseX, int mouseY);
    string getText() const; 
    void setActive(bool state);
};

#endif