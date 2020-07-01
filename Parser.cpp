
#include<string>
#include<iostream>
#include"Parser.h"

void Parser::throwErrors(ItemCur &cursor, std::string s) {
    std::stringstream ss;
    std::string err;
    ss << cursor->Getcursor().first << ", " << cursor->Getcursor().second << ": " << s;
    getline(ss, err);
    
    errors.push(err);

    ItemCur nextcur = cursor;
    while(nextcur->GetType() != FINISH && nextcur->Getcursor().first == cursor->Getcursor().first)
        nextcur++;
    cursor = nextcur;
}

//<分程序> ::= [<常量说明部分>][变量说明部分>]{<过程说明部分>}<语句>
int Parser::program(ItemCur &cursor) {
    bool empty = true;
    if(constDeclaration(cursor) == 0)
        empty = false;
    if(varDeclaration(cursor) == 0)
        empty = false;

    while(procedureDeclaration(cursor) == 0)   
        empty = false;

    if(clause(cursor) == 0)
        empty = false;
    
    return empty ? -1 : 0;
}
//<常量说明部分> ::= const<常量定义>{,<常量定义>};
int Parser::constDeclaration(ItemCur &cursor) {
    if(cursor->GetType() != CONST) {
        //EMPTY
        return -1;
    }
    cursor++;

    if(constDefinition(cursor)) {
        //HANDLED ERROR
        return -1;
    }

    while(1) {
        if(cursor->GetType() != COMMA) {
            break; 
        }
        cursor++;

        if(constDefinition(cursor)) {
            //HANDLED ERROR
            break;
        }
    }

    if(cursor->GetType() != SEMICOLON) {
        throwErrors(cursor, "\";\" needed");
        return -1;
    }
    cursor++;

    return 0;
}
//<常量定义> ::= <标识符>=<无符号整数>
int Parser::constDefinition(ItemCur &cursor) {
    if(identifier(cursor)) {
        throwErrors(cursor, "const definition error");
        return -1;
    }

    if(cursor->GetType() != EQU) {
        throwErrors(cursor, "\'=\' needed");
        return -1;
    }
    cursor++;

    if(integer(cursor)) {
        throwErrors(cursor, "initial value needed");
        return -1;
    }

    return 0;
}
//<无符号整数> ::= <数字>{<数字>}
int Parser::integer(ItemCur &cursor) {
    if(cursor->GetType() != NUMBER) {
        //THROW ERROR
        return -1;
    }
    cursor++;

    return 0;
}
//<标识符> ::= <字母>{<字母>|<数字>}
int Parser::identifier(ItemCur &cursor) {
    if(cursor->GetType() != IDENT) {
        //THROW ERROR
        return -1;
    }
    cursor++;

    return 0;
}
//<变量说明部分>::= var<标识符>{,<标识符>};
int Parser::varDeclaration(ItemCur &cursor) {
    if(cursor->GetType() != VAR) {
        //EMPTY
        return -1;
    }
    cursor++;

    if(identifier(cursor)) {
        throwErrors(cursor, "ilegal identifier");
        return -1;
    }

    while(1) {
        if(cursor->GetType() != COMMA) {
            break; 
        }
        cursor++;

        if(identifier(cursor)) {
            throwErrors(cursor, "identifier needed");
            break;
        }
    }

    if(cursor->GetType() != SEMICOLON) {
        throwErrors(cursor, "\";\" needed");
        return -1;
    }
    cursor++;

    return 0;
}
//<过程说明部分> ::= <过程首部><分程序>；
int Parser::procedureDeclaration(ItemCur &cursor) {
    if(procedureHeader(cursor)) {
        //EMPTY or ERROR
        return -1;
    }
    if(program(cursor)) {
        throwErrors(cursor, "salve program needed");
        return -1;
    }

    if(cursor->GetType() != SEMICOLON) {
        throwErrors(cursor, "\";\" needed");
        return -1;
    }
    cursor++;

    return 0;
}
//<过程首部> ::= procedure<标识符>;
int Parser::procedureHeader(ItemCur &cursor) {
    if(cursor->GetType() != PROCEDURE) {
        //EMPTY
        return -1;
    }
    cursor++;

    if(identifier(cursor)) {
        throwErrors(cursor, "\"identifier\" needed");
        return -1;
    }
    if(cursor->GetType() != SEMICOLON) {
        throwErrors(cursor, "\";\" needed");
        return -1;
    }
    cursor++;

    return 0;
}
//<语句> ::= <赋值语句>|<条件语句>|<当型循环语句>|<过程调用语句>|<读语句>|<写语句>|<复合语句>|<重复语句>|<空>
int Parser::clause(ItemCur &cursor) {
    
    if(assignClause(cursor) == 0) {
        return 0;
    }

    if(condiClause(cursor) == 0) {
        return 0;
    }

    if(whileClause(cursor) == 0) {
        return 0;
    }

    if(callClause(cursor) == 0) {
        return 0;
    }

    if(readClause(cursor) == 0) {
        return 0;
    }

    if(writeClause(cursor) == 0) {
        return 0;
    }

    if(complexClause(cursor) == 0) {
        return 0;
    }

    if(repeatClause(cursor) == 0) {
        return 0;
    }

    //EMPTY
    return 0;
}
//<赋值语句> ::= <标识符>:=<表达式>
int Parser::assignClause(ItemCur &cursor) {
    if(identifier(cursor)) {
        //EMPTY
        return -1;
    }
    if(cursor->GetType() != BECOMES) {
        throwErrors(cursor, "\":=\" needed");
        return -1;
    }
    cursor++;
    if(expression(cursor)) {
        throwErrors(cursor, "identifier or expression needed");
        return -1;
    }

    return 0;
}
//<表达式> ::= [+|-]<项>{<加法运算符><项>}
int Parser::expression(ItemCur &cursor) {
    plusOper(cursor);
    if(term(cursor)) {
        //EMPTY
        return -1;
    }
    while(1) {
        if(plusOper(cursor)) {
            break;
        }
        if(term(cursor)) {
            throwErrors(cursor, "incomplete expression");
            return -1;
        }
    }

    return 0;
}
//<项> ::= <因子>{<乘法运算符><因子>}
int Parser::term(ItemCur &cursor) {
    if(factor(cursor)) {
        //EMPTY
        return -1;
    }

    while(1) {
        if(timesOper(cursor)) {
            break;
        }

        if(factor(cursor)) {
            throwErrors(cursor, "incomplete expression");
            return -1;
        }
    }

    return 0;
}
//<因子> ::= <标识符>|<无符号整数>|'('<表达式>')'
int Parser::factor(ItemCur &cursor) {
    if(identifier(cursor) == 0) {
        return 0;
    }

    if(cursor->GetType() == NUMBER) {
        cursor++;
        return 0;
    }

    if(cursor->GetType() == LPAREN) {
        cursor++;
        if(expression(cursor)) {
            throwErrors(cursor, "expression needed");
            return -1;
        }
        if(cursor->GetType() != RPAREN) {
            throwErrors(cursor, "\")\" needed");
            return -1;
        }
        cursor++;
        return 0;
    }

    //EMPTY
    return -1;
}
//<加法运算符> ::= +|-
int Parser::plusOper(ItemCur &cursor) {
    if(cursor->GetType() == PLUS || cursor->GetType() == MINUS) {
        cursor++;
        return 0;
    }

    //NOT PLUS OPER
    return -1;
}
//<乘法运算符> ::= *|/
int Parser::timesOper(ItemCur &cursor) {
    if(cursor->GetType() == TIMES || cursor->GetType() == DIV) {
        cursor++;
        return 0;
    }

    //NOT TIMES OPER
    return -1;
}
//<条件> ::= <表达式><关系运算符><表达式> | odd<表达式>
int Parser::condi(ItemCur &cursor) {
    if(expression(cursor)) {
        //EMPTY
        return -1;
    }
    if(RelationOper(cursor)) {
        //odd
        return -1;
    }
    if(expression(cursor)) {
        throwErrors(cursor, "expression needed");
        return -1;
    }
    return 0;
}
//<关系运算符> ::= =|<>|<|<=|>|>=
int Parser::RelationOper(ItemCur &cursor) {
    switch (cursor->GetType())
    {
    case EQU:
    case NEQ:
    case LSS:
    case LEQ:
    case GTR:
    case GEQ:
        cursor++;
        break;

    default:
        //NOT RELATION OPER
        return -1;
    }

    return 0;
}
//<条件语句> ::= if<条件>then<语句>[else<语句>]
int Parser::condiClause(ItemCur &cursor) {
    if(cursor->GetType() != IF) {
        //EMPTY
        return -1;
    }
    cursor++;
    if(condi(cursor)) {
        throwErrors(cursor, "condition needed");
        return -1;
    }
    if(cursor->GetType() != THEN) {
        throwErrors(cursor, "\"then\" needed");
        return -1;
    }
    cursor++;
    if(clause(cursor)) {
        throwErrors(cursor, "incomplete condition clause");
        return -1;
    }

    if(cursor->GetType() == ELSE) {
        cursor++;
        if(clause(cursor)) {
            throwErrors(cursor, "incomplete condition clause");
            return -1;
        }
    }

    return 0;
}
//<当型循环语句> ::= while<条件>do<语句>
int Parser::whileClause(ItemCur &cursor) {
    if(cursor->GetType() != WHILE) {
        //EMPTY
        return -1;
    }
    cursor++;
    if(condi(cursor)) {
        throwErrors(cursor, "condition needed");
        return -1;
    }

    if(cursor->GetType() != DO) {
        throwErrors(cursor, "\"do\" needed");
        return -1;
    }
    cursor++;

    if(clause(cursor)) {
        throwErrors(cursor, "incomplete while clause");
        return -1;
    }

    return 0;
}
//<过程调用语句> ::= call<标识符>
int Parser::callClause(ItemCur &cursor) {
    if(cursor->GetType() != CALL) {
        //EMPTY
        return -1;
    }
    cursor++;
    if(identifier(cursor)) {
        throwErrors(cursor, "imcomplete call clause, identifier needed");
        return -1;
    }

    return 0;
}
//<复合语句> ::= begin<语句>{;<语句>}end
int Parser::complexClause(ItemCur &cursor) {
    if(cursor->GetType() != BEGIN) {
        //EMPTY
        return -1;
    }
    cursor++;

    if(clause(cursor)) {
        //EMPTY
        return -1;
    }

    while(1) {
        if(cursor->GetType() != SEMICOLON) {
            break;
        }
        cursor++;

        if(clause(cursor)) {
            throwErrors(cursor, "unexpect \";\", clause needed");
            return -1;
        }
    }

    if(cursor->GetType() != END) {
        throwErrors(cursor, "\"end\" needed");
        return -1;
    }
    cursor++;

    return 0;
}
//<重复语句> ::= repeat<语句>{;<语句>}until<条件>
int Parser::repeatClause(ItemCur &cursor) {
    if(cursor->GetType() != REPEAT) {
        //EMPTY
        return -1;
    }
    cursor++;

    if(clause(cursor)) {
        //EMPTY
        return -1;
    }

    while(1) {
        if(cursor->GetType() != SEMICOLON) {
            break;
        }
        cursor++;

        if(clause(cursor)) {
            throwErrors(cursor, "unexpect \";\", clause needed");
            return -1;
        }
    }

    if(cursor->GetType() != UNTIL) {
        throwErrors(cursor, "\"until\" needed");
        return -1;
    }
    cursor++;

    if(condi(cursor)) {
        throwErrors(cursor, "incomplete repeat clause, condition needed");
        return -1;
    }

    return 0;
}
//<读语句> ::= read'('<标识符>{,<标识符>}')'
int Parser::readClause(ItemCur &cursor) {
    if(cursor->GetType() != READ) {
        //EMPTY
        return -1;
    }
    cursor++;

    if(cursor->GetType() != LPAREN) {
        throwErrors(cursor, "\"(\" needed");
        return -1;
    }
    cursor++;

    if(identifier(cursor)) {
        return -1;
    }

    while(1) {
        if(cursor->GetType() != COMMA) {
            break;
        }
        cursor++;

        if(identifier(cursor)) {
            throwErrors(cursor, "identifier needed");
            return -1;
        }
    }

    if(cursor->GetType() != RPAREN) {
        throwErrors(cursor, "\")\" needed");
        return -1;
    }
    cursor++;

    return 0;
}
//<写语句> ::= write'('<标识符>{,<标识符>}')'
int Parser::writeClause(ItemCur &cursor) {
    if(cursor->GetType() != WRITE) {
        return -1;
    }
    cursor++;

    if(cursor->GetType() != LPAREN) {
        throwErrors(cursor, "\"(\" needed");
        return -1;
    }
    cursor++;

    if(identifier(cursor)) {
        return -1;
    }

    while(1) {
        if(cursor->GetType() != COMMA) {
            break;
        }
        cursor++;

        if(identifier(cursor)) {
            throwErrors(cursor, "identifier needed");
            return -1;
        }
    }

    if(cursor->GetType() != RPAREN) {
        throwErrors(cursor, "\")\" needed");
        return -1;
    }
    cursor++;

    return 0;
}

int Parser::MainParser(ItemCur cursor, const ItemCur &_end) {
    this->endcur = _end;
    if(program(cursor)) {
        return -1;
    }
    if(cursor->GetType() != PERIOD) {
        throwErrors(cursor, "\".\" needed");
        return -1;
    }
    cursor++;
    if(cursor->GetType() != FINISH) {
        throwErrors(cursor, "unexpect items after program");
        return -1;
    }
    return 0;
}