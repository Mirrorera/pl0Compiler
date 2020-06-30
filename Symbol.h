
#pragma once
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
const std::string SIGN[] = {
    "+",
    "-",
    "*",
    "/",
    "<>",
    "<",
    "<=",
    ">",
    ">=",
    "=",
    ":=",
    ",",
    ".",
    ";",
    "(",
    ")"
};

enum ITEM_TYPE {
    BEGIN = 0,
    END = 1,
    IF = 2,
    THEN = 3,
    ELSE = 4,
    CONST = 5,
    PROCEDURE = 6,
    VAR = 7,
    DO = 8,
    WHILE = 9,
    CALL = 10,
    READ = 11,
    WRITE = 12,
    REPEAT = 13,
    UNTIL = 14,

    PLUS = 15,
    MINUS = 16,
    TIMES = 17,
    DIV = 18,
    NEQ = 19,
    LSS = 20,
    LEQ = 21,
    GTR = 22,
    GEQ = 23,
    EQU = 24,
    BECOMES = 25,
    COMMA = 26,
    PERIOD = 27,
    SEMICOLON = 28,
    LPAREN = 29,
    RPAREN = 30,

    IDENT = 31,

    NUMBER = 32,

    NOT_KEYWORD = -1,
    NOT_SIGN = -2,
    NOT_IDENT = -3
};

const std::string ITEM_TYPE_NAME[] = {
    "BEGIN",
    "END",
    "IF",
    "THEN",
    "ELSE",
    "CONST",
    "PROCEDURE",
    "VAR",
    "DO",
    "WHILE",
    "CALL",
    "READ",
    "WRITE",
    "REPEAT",
    "UNTIL",

    "PLUS",
    "MINUS",
    "TIMES",
    "DIV",
    "NEQ",
    "LSS",
    "LEQ",
    "GTR",
    "GEQ",
    "EQU",
    "BECOMES",
    "COMMA",
    "PERIOD",
    "SEMICOLON",
    "LPAREN",
    "RPAREN",

    "IDENT",

    "NUMBER",
};

bool IsKeyword(std::string s);
bool IsSign(std::string s);

ITEM_TYPE GetKeyWordType(std::string s);
ITEM_TYPE GetSignType(std::string s);