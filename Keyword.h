
#include<string>

const std::string KEYWORD[] = {
    "begin",
    "end", 
    "if",
    "then",
    "else",
    "const",
    "procedure",
    "var",
    "do",
    "while",
    "call",
    "read",
    "write",
    "repeat",
    "until"
};

bool IsKeyword(string s) {
    for (auto &&key : KEYWORD)
    {
        if(key == s) {
            return true;
        }
    }
    return false;
}