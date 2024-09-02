#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <cstdint>
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::make_pair;
using std::string;

class WordTable{
    vector<string *> words;
    public:
    WordTable();
    ~WordTable();
    int charHash(char c, int index, int size);
};