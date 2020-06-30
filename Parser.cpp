
#include<string>
#include"Parser.h"

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
        return -1;
    }
    cursor++;

    if(constDefinition(cursor)) {
        //_ERROR_
        return -1;
    }

    while(1) {
        if(cursor->GetType() != COMMA) {
            break; 
        }
        cursor++;

        if(constDefinition(cursor)) {
            //_ERROR_
            break;
        }
    }

    if(cursor->GetType() != SEMICOLON) {
        //_ERROR_
        return -1;
    }
    cursor++;

    return 0;
}
//<常量定义> ::= <标识符>=<无符号整数>
int Parser::constDefinition(ItemCur &cursor) {
    if(identifier(cursor)) {
        return -1;
    }

    if(cursor->GetType() != EQU) {
        return -1;
    }
    cursor++;

    if(integer(cursor)) {
        return -1;
    }

    return 0;
}
//<无符号整数> ::= <数字>{<数字>}
int Parser::integer(ItemCur &cursor) {
    if(cursor->GetType() != NUMBER) {
        return -1;
    }
    cursor++;

    return 0;
}
//<标识符> ::= <字母>{<字母>|<数字>}
int Parser::identifier(ItemCur &cursor) {
    if(cursor->GetType() != IDENT) {
        return -1;
    }
    cursor++;

    return 0;
}
//<变量说明部分>::= var<标识符>{,<标识符>};
int Parser::varDeclaration(ItemCur &cursor) {
    if(cursor->GetType() != VAR) {
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
            //_ERROR_
            break;
        }
    }

    if(cursor->GetType() != SEMICOLON) {
        return -1;
    }
    cursor++;

    return 0;
}
//<过程说明部分> ::= <过程首部><分程序>；
int Parser::procedureDeclaration(ItemCur &cursor) {
    if(procedureHeader(cursor)) {
        return -1;
    }
    if(identifier(cursor)) {
        return -1;
    }

    if(cursor->GetType() != SEMICOLON) {
        return -1;
    }
    cursor++;

    return 0;
}
//<过程首部> ::= procedure<标识符>;
int Parser::procedureHeader(ItemCur &cursor) {
    if(cursor->GetType() != PROCEDURE) {
        return -1;
    }
    cursor++;

    if(cursor->GetType() != SEMICOLON) {
        return -1;
    }
    cursor++;
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

    return 0;
}
//<赋值语句> ::= <标识符>:=<表达式>
int Parser::assignClause(ItemCur &cursor) {
    if(identifier(cursor)) {
        return -1;
    }
    if(cursor->GetType() != BECOMES) {
        return -1;
    }
    cursor++;
    if(expression(cursor)) {
        return -1;
    }

    return 0;
}
//<表达式> ::= [+|-]<项>{<加法运算符><项>}
int Parser::expression(ItemCur &cursor) {
    plusOper(cursor);
    if(term(cursor)) {
        return -1;
    }
    while(1) {
        if(plusOper(cursor)) {
            break;
        }
        if(term(cursor)) {
            return -1;
        }
    }

    return 0;
}
//<项> ::= <因子>{<乘法运算符><因子>}
int Parser::term(ItemCur &cursor) {
    if(factor(cursor)) {
        return -1;
    }

    while(1) {
        if(timesOper(cursor)) {
            break;
        }

        if(factor(cursor)) {
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
            return -1;
        }
        if(cursor->GetType() != RPAREN) {
            return -1;
        }
        cursor++;
        return 0;
    }

    return -1;
}
//<加法运算符> ::= +|-
int Parser::plusOper(ItemCur &cursor) {
    if(cursor->GetType() == PLUS || cursor->GetType() == MINUS) {
        cursor++;
        return 0;
    }

    return -1;
}
//<乘法运算符> ::= *|/
int Parser::timesOper(ItemCur &cursor) {
    if(cursor->GetType() == TIMES || cursor->GetType() == DIV) {
        cursor++;
        return 0;
    }
    return -1;
}
//<条件> ::= <表达式><关系运算符><表达式>
int Parser::condi(ItemCur &cursor) {
    if(expression(cursor)) {
        return -1;
    }
    if(RelationOper(cursor)) {
        return -1;
    }
    if(expression(cursor)) {
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
        return -1;
    }

    return 0;
}
//<条件语句> ::= if<条件>then<语句>[else<语句>]
int Parser::condiClause(ItemCur &cursor) {
    if(cursor->GetType() != IF) {
        return -1;
    }
    cursor++;
    if(condi(cursor)) {
        return -1;
    }
    if(cursor->GetType() != THEN) {
        return -1;
    }
    cursor++;
    if(clause(cursor)) {
        return -1;
    }

    if(cursor->GetType() == ELSE) {
        cursor++;
        if(clause(cursor)) {
            return -1;
        }
    }

    return 0;
}
//<当型循环语句> ::= while<条件>do<语句>
int Parser::whileClause(ItemCur &cursor) {
    if(cursor->GetType() != WHILE) {
        return -1;
    }
    cursor++;
    if(condi(cursor)) {
        return -1;
    }

    if(cursor->GetType() != DO) {
        return -1;
    }
    cursor++;

    if(clause(cursor)) {
        return -1;
    }

    return 0;
}
//<过程调用语句> ::= call<标识符>
int Parser::callClause(ItemCur &cursor) {
    if(cursor->GetType() != CALL) {
        return -1;
    }
    cursor++;
    if(identifier(cursor)) {
        return -1;
    }

    return 0;
}
//<复合语句> ::= begin<语句>{;<语句>}end
int Parser::complexClause(ItemCur &cursor) {
    if(cursor->GetType() != BEGIN) {
        return -1;
    }
    cursor++;

    if(clause(cursor)) {
        return -1;
    }

    while(1) {
        if(cursor->GetType() != SEMICOLON) {
            break;
        }
        cursor++;

        if(clause(cursor)) {
            return -1;
        }
    }

    if(cursor->GetType() != END) {
        return -1;
    }
    cursor++;

    return 0;
}
//<重复语句> ::= repeat<语句>{;<语句>}until<条件>
int Parser::repeatClause(ItemCur &cursor) {
    if(cursor->GetType() != REPEAT) {
        return -1;
    }
    cursor++;

    if(clause(cursor)) {
        return -1;
    }

    while(1) {
        if(cursor->GetType() != SEMICOLON) {
            break;
        }
        cursor++;

        if(clause(cursor)) {
            return -1;
        }
    }

    if(cursor->GetType() != UNTIL) {
        return -1;
    }
    cursor++;

    if(condi(cursor)) {
        return -1;
    }

    return 0;
}
//<读语句> ::= read'('<标识符>{,<标识符>}')'
int Parser::readClause(ItemCur &cursor) {
    if(cursor->GetType() != READ) {
        return -1;
    }
    cursor++;

    if(cursor->GetType() != LPAREN) {
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
            return -1;
        }
    }

    if(cursor->GetType() != RPAREN) {
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
            return -1;
        }
    }

    if(cursor->GetType() != RPAREN) {
        return -1;
    }
    cursor++;

    return 0;
}

