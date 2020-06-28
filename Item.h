
#pragma once
#include<string>
#include<ostream>

enum ITEM_TYPE {
    KEY_WORD,
    IDENTIFIER,
    SIGNER,
    NUMBER
};

class Item {
private:
    ITEM_TYPE   type;
    std::string s_content;
    int         i_content;

public:
    Item() = default;
    Item(int n);
    Item(std::string s, ITEM_TYPE type);

    std::string ToString()const;
    int         ToInt()const;

    int  GetType()const;
    void SetType(int _type);

    void SetContent(std::string);
    void SetContent(int);

};

std::ostream & operator<<(std::ostream &os, Item item);