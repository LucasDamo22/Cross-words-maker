#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::make_pair;
using std::string;

class WordTable{
    std::unordered_map<int, vector<string>> map;
    public:
    WordTable();
    ~WordTable();
    int charHash(char c, int index, int size);
    void add_word(string word);
    vector<string> get_words(char c, int index, int size);

};