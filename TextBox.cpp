#include "TextBox.h"

TextBox::TextBox(string placeholder, int x, int y, int w, int h, typeBox boxType):box({x,y,w,h}){
    this->text = "";
    this->is_active = false;
    startPos = 0;
    this->placeholder = placeholder;
    this->boxType = boxType;
}

void TextBox::handleEvent(SDL_Event& e){
    if (!is_active) return;
    if (e.type == SDL_TEXTINPUT) {
        // Thêm ký tự vào chuỗi (Nếu không phải là ký tự điều khiển)
        if (strlen(e.text.text) > 0) {
            text += e.text.text;
        }
    } else if (e.type == SDL_KEYDOWN){
        // Xử lý phím đặc biệt (Backspace)
        if (e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
            text.pop_back(); // Xóa ký tự cuối
            if (startPos > 0) startPos--;
        }
    }
}

void TextBox::render(SDL_Renderer* renderer, TTF_Font* font){
    if(boxType == FILL){
        box.FillRect(renderer, white);
        box.drawRect(renderer, black);
    }
    else if(boxType == UNDERLINE){
        box.drawRect(renderer, black);
        Texture line;
        line.setRect(box.getRect().x, box.getRect().y + box.getRect().h - 4, box.getRect().w, 4);
        line.FillRect(renderer, black);
    }

    // ve placeholder
    if(!is_active && text.empty()){
        Texture placeholderText;
        placeholderText.write(renderer, font, placeholder, gray);
        int length = placeholderText.getRect().w*box.getRect().h/placeholderText.getRect().h;
        placeholderText.setRect(box.getRect().x + 5, box    .getRect().y + box.getRect().h*2/10, length, box.getRect().h*7/10);
        placeholderText.render(renderer);
        return;
    }

    //ve con tro |
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
        string displayText = text.substr(startPos, text.size() - startPos);

        Texture textTexture;    
        textTexture.write(renderer, font, displayText, black);
        int length = textTexture.getRect().w*box.getRect().h/textTexture.getRect().h;
        textTexture.setRect(box.getRect().x + 5, box.getRect().y + box.getRect().h*2/10, length, box.getRect().h*7/10);
        
        while(textTexture.getRect().w > box.getRect().w -10){
            startPos++;
            displayText = text.substr(startPos, text.size() - startPos);
            textTexture.write(renderer, font, displayText, black);
            length = textTexture.getRect().w*box.getRect().h/textTexture.getRect().h;
            textTexture.setRect(box.getRect().x + 5, box.getRect().y + box.getRect().h*2/10, length, box.getRect().h*7/10);
        }
        
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
void TextBox::clearText(){
    this->text = "";
    this->startPos = 0;
}