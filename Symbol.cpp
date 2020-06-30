
#include<string>
#include"Symbol.h"

bool IsKeyword(std::string s) {
    for (auto &&key : KEYWORD)
    {
        if(key == s) {
            return true;
        }
    }
    return false;
}

bool IsSign(std::string s) {
    for (auto &&sign : SIGN)
    {
        if(s == sign) {
            return true;
        }
    }

    return false;
}

ITEM_TYPE GetKeyWordType(std::string s) {
    int t = 0;
    for (auto &&key : KEYWORD)
    {
        if(s == key) {
            return ITEM_TYPE(t);
        }
        ++t;
    }
    return NOT_KEYWORD;
}


ITEM_TYPE GetSignType(std::string s) {
    int t = 15;
    for (auto &&sign : SIGN)
    {
        if(s == sign) {
            return ITEM_TYPE(t);
        }
        ++t;
    }
    return NOT_SIGN;
}