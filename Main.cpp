
#include <iostream>
#include <vector>
#include <string>

#include "Analyzer.h"
#include "Item.h"

int main() {
    using namespace std;

    vector<Item>* wordList = new vector<Item>();
    string s_input;
    char ch;
    while(cin.get(ch)) {
        s_input.push_back(ch);
    }
    
    Analyzer(s_input.begin(), s_input.end(), wordList);

    for (auto &&item : *wordList)
    {
        cout << item << endl;
    }
    
    return 0;
}