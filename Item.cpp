
#include<string>
#include"Item.h"


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

std::ostream & operator<< (std::ostream &os, Item item) {
    std::string type;
    switch (item.GetType())
    {
    case KEY_WORD:
        type = "KEY_WORD";
        break;
    case IDENTIFIER:
        type = "IDENTIFIER";
        break;
    case SIGNER:
        type = "SIGNER";
        break;
    case NUMBER:
        type = "NUMBER";
        break;
    default:
        break;
    }

    if(item.GetType() == NUMBER) {
        os << item.ToInt() << " : " << type;
    } else {
        os << item.ToString() << " : " << type;
    }

    return os;
}