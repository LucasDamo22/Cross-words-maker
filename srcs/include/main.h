#include <iostream>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <fstream>
//ia
#include <algorithm>  // For std::remove_if and std::isspace
#include <cctype>     // For std::isspace
//ia

// //#include "./include/Slot.h"
// #include "Word.h"
#include "Grid.h"



using std::unordered_set;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair; 



int main(int argc, char* argv[]);
std::vector<std::string> readStringsFromFile(const std::string& filename);
std::string trim_trailing_whitespace(const std::string &str);
bool already_exists(unordered_set<string> &words_check, string word);


