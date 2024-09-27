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
    std::unordered_map<int, vector<string*>> map_p;
    WordTable();
    ~WordTable();
    int charHash(char c, int index, int size);
    int charHash_p(char *c, int index, int size);
    void add_word(string word);
    void add_word_p(string *word);
    vector<string> get_words(char c, int index, int size);
    vector<string*> get_words_p(char c, int index, int size);

};