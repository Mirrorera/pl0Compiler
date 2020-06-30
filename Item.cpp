
#include<string>
#include<utility>
#include"Item.h"
#include"Symbol.h"


Item::Item(int n) {
    this->i_content = n;
    this->type = NUMBER;
}
Item::Item(std::string s, ITEM_TYPE type) {
    this->s_content = s;
    this->type = type;
}

std::string Item::ToString() const {
    return this->s_content;
}
int Item::ToInt() const {
    return this->i_content;
}
int Item::GetType() const {
    return this->type;
}

void Item::SetType(int _type) {
    this->type = type;
}

void Item::SetContent(std::string s) {
    this->s_content = s;
}
void Item::SetContent(int n) {
    this->i_content = n;
}


void Item::SetCursor(int l, int c) {
    this->cursor = std::make_pair(l, c);
}
std::pair<int, int> Item::Getcursor() {
    return this->cursor;
}

std::ostream & operator<< (std::ostream &os, Item item) {
    std::string type;
    
    if (item.GetType() >= 0 && item.GetType() <= 14) {
        type = "KEYWORD";
    } else if (item.GetType() <= 30){
        type = "SIGN";
    } else if (item.GetType() == IDENT) {
        type = "IDENT";
    } else if (item.GetType() == NUMBER) {
        type = "NUMBER";
    } else {
        type = "ERROR";
    }

    if(item.GetType() == NUMBER) {
        os << item.ToInt() << " : " << type << " (" << item.Getcursor().first << ", " << item.Getcursor().second << ") ";
    } else {
        os << item.ToString() << " : " << type << " (" << item.Getcursor().first << ", " << item.Getcursor().second << ") ";
    }

    return os;
}