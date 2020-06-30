
#include<string>
#include<vector>
#include<queue>
#include"Item.h"

typedef std::vector<Item>::iterator ItemCur;

static class Parser {
private:
    std::queue<std::string> errors;

    int program(ItemCur &cursor);
    
    int constDeclaration(ItemCur &cursor);
    int constDefinition(ItemCur &cursor);

    int integer(ItemCur &cursor);
    
    int identifier(ItemCur &cursor);

    int varDeclaration(ItemCur &cursor);

    int procedureDeclaration(ItemCur &cursor);
    int procedureHeader(ItemCur &cursor);

    int clause(ItemCur &cursor);
    int assignClause(ItemCur &cursor);

    int expression(ItemCur &cursor);
    int term(ItemCur &cursor);
    int factor(ItemCur &cursor);

    int plusOper(ItemCur &cursor);
    int timesOper(ItemCur &cursor);

    int condi(ItemCur &cursor);
    int RelationOper(ItemCur &cursor);
    int condiClause(ItemCur &cursor);
    int whileClause(ItemCur &cursor);

    int callClause(ItemCur &cursor);
    int complexClause(ItemCur &cursor);
    int repeatClause(ItemCur &cursor);

    int readClause(ItemCur &cursor);
    int writeClause(ItemCur &cursor);

public:
    int MainParser(ItemCur &cursor, const ItemCur &end) {
        if(program(cursor)) {
            return -1;
        }
        cursor++;
        if(cursor != end) {
            return -1;
        }

        return 0;
    }
};