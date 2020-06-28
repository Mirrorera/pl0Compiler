
#pragma once
#include<string>
#include<vector>

#include"Item.h"

using std::vector;
using std::string;
using std::stringstream;

int Analyzer(string::iterator p_data, const string::iterator &p_end, vector<Item>* receiver);

string NextDigit(string::iterator &p_data, const string::iterator &p_end);
string NextIdentifier(string::iterator &p_data, const string::iterator &p_end);
string NextSigner(string::iterator &p_data, const string::iterator &p_end);