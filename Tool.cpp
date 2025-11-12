#include "Tool.h"

Tool::Tool(bool h) : hold(h) {}
 
Tool::~Tool() {}

void Tool::setHold(bool h) {
    hold = h;
}
bool Tool::getHold() {
    return hold;
}

