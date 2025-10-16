#include "TextBox.h"

TextBox::TextBox(int x, int y, int w, int h ):box({x,y,w,h}){
    this->text = "";
    this->is_active = false;
}

void TextBox::handleEvent(SDL_Event& e){
    if (!is_active) return;
    if (e.type == SDL_TEXTINPUT) {
        // Thêm ký tự vào chuỗi (Nếu không phải là ký tự điều khiển)
        if (strlen(e.text.text) > 0) {
            text += e.text.text;
        }
    } else if (e.type == SDL_KEYDOWN) {
        // Xử lý phím đặc biệt (Backspace)
        if (e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
            text.pop_back(); // Xóa ký tự cuối
        }
    }
}

void TextBox::render(SDL_Renderer* renderer, TTF_Font* font){
    this->box.FillRect(renderer, white);
    this->box.drawRect(renderer, black);
    //ve contro |
    if(this->is_active && (SDL_GetTicks()/500)%2 && text.empty()){
        //int length = text.size()*box.getRect().h/2;
        //int length = textTexture.getRect().w*box.getRect().h/textTexture.getRect().h;
        int length = 0;
        Texture tro;
        tro.setRect(box.getRect().x + length +5, box.getRect().y + box.getRect().h*1/10, 2, box.getRect().h*8/10);
        tro.FillRect(renderer, black);
    }

    //ve chu
    if(!text.empty()){
        Texture textTexture;
        textTexture.write(renderer, font, text, black);

        // int length = text.size()*box.getRect().h/2;
        int length = textTexture.getRect().w*box.getRect().h/textTexture.getRect().h;
        // length = (length > box.getRect().w - 10 )?box.getRect().w - 10 : length;
        textTexture.setRect(box.getRect().x + 5, box.getRect().y + box.getRect().h*2/10, length, box.getRect().h*7/10);
        textTexture.render(renderer);
        if(this->is_active && (SDL_GetTicks()/500)%2){
            Texture tro;
            tro.setRect(textTexture.getRect().x + textTexture.getRect().w, box.getRect().y + box.getRect().h*1/10, 2, box.getRect().h*8/10);
            tro.FillRect(renderer, black);
        }
        textTexture.free();
    }
}

bool TextBox::checkClick(int mouseX, int mouseY){
    return (mouseX >= box.getRect().x && mouseX < box.getRect().x + box.getRect().w &&
            mouseY >= box.getRect().y && mouseY < box.getRect().y + box.getRect().h);
}

string TextBox::getText() const { return text; }

void TextBox::setActive(bool state) { is_active = state; }