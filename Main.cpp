
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Analyzer.h"
#include "Item.h"
#include "Symbol.h"
#include "Parser.h"


int main(int argc, char **argv) {
    using namespace std;

    ifstream fin(argv[1]);

    vector<Item>* wordList = new vector<Item>();
    string s_input;
    char ch;
    while(fin.get(ch)) {
        s_input.push_back(ch);
    }
    
    Analyzer(s_input.begin(), s_input.end(), wordList);

    for (auto &&item : *wordList)
    {
        if(item.GetType() == FINISH) {
            break;
        }
        cout << item << endl;
        cout << "#" << ITEM_TYPE_NAME[item.GetType()] << endl;
    }
    
    Parser parser;
    
    parser.MainParser(wordList->begin(), wordList->end());
    if(parser.errors.empty()) {
        cout << "Parse successfully, 0 error." << endl;
    } else {
        int n = parser.errors.size();
        cout << "Parse failed, " << n << " error." << endl;
        while(!parser.errors.empty()) {
            cout << parser.errors.front() << endl;
            parser.errors.pop();
        }
    }
    return 0;
}