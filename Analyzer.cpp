
#include<string>
#include<vector>
#include<cstdio>
#include<sstream>
#include<assert.h>

#include"Analyzer.h"
#include"Symbol.h"
#include"Item.h"

using std::vector;
using std::string;
using std::stringstream;


int Analyzer(string::iterator p_data, const string::iterator &p_end, vector<Item>* receiver) {
    receiver->clear();
    int line = 1;
    string::iterator line_begin = p_data;

    if(p_data == p_end) {
        return 0;
    }

    while(p_data < p_end) {
        Item item;

        if (isblank(*p_data) || iscntrl(*p_data)) {
            if(*p_data == '\n') {
                line++;
                line_begin = p_data;
                line_begin++;
            }
            p_data++;
            continue;    
        }

        if (isdigit(*p_data)) {
            string s = NextDigit(p_data, p_end);
            stringstream ss(s);
            int n;
            ss >> n;

            item = Item(n);

            item.SetCursor(line, (p_data - line_begin));
            receiver->push_back(item);
            continue;
        }

        if (isalpha(*p_data)) {
            string s = NextIdentifier(p_data, p_end);

            if(IsKeyword(s)) {
                item = Item(s, GetKeyWordType(s));
            } else {
                item = Item(s, IDENT);
            }

            item.SetCursor(line, (p_data - line_begin));
            receiver->push_back(item);
            continue;
        }

        if (true) {
            string s = NextSign(p_data, p_end);

            item = Item(s, GetSignType(s));

            item.SetCursor(line, (p_data - line_begin));
            receiver->push_back(item);
        }

        
    }

    return 0;
}


string NextDigit(string::iterator &p_data, const string::iterator &p_end) {
    string ans;

    while(p_data < p_end) {
        if(isblank(*p_data) || iscntrl(*p_data)) {
            break;
        }
        if(!isdigit(*p_data)) {
            break;
        }

        ans.push_back(*p_data);
        ++p_data;
    }

    return ans;
}

string NextIdentifier(string::iterator &p_data, const string::iterator &p_end) {
    string ans;

    while(p_data < p_end) {
        if(isblank(*p_data) || iscntrl(*p_data)) {
            break;
        }
        if(!isalnum(*p_data) && !(*p_data == '_')) {
            break;
        }

        ans.push_back(*p_data);
        ++p_data;
    }

    return ans;

    
}
string NextSign(string::iterator &p_data, const string::iterator &p_end) {
    string ans;

    while(p_data < p_end) {
        if(isblank(*p_data) || iscntrl(*p_data)) {
            break;
        }
        if(isalnum(*p_data)) {
            break;
        }

        ans.push_back(*p_data);
        ++p_data;
    }
    
    return ans;
}