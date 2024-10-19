#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <thread>
#include <chrono>
//#include "Slot.h"
#include "WordTable.h"

using std::pair;
using std::find;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::unordered_set;

class Grid{
    public:
        
        vector<Slot> slots;
        unordered_set<string> used_words;
        int most_dependencies;
        
        
        Grid();
        ~Grid();
        void add_slot(Slot slot);
        void create_grid(vector<vector<char>> matrix);
        void horizontal_search_2(vector<vector<char>> &matrix);
        void vertical_search_2(vector<vector<char>> &matrix);
        vector<Slot*> get_slots();
        void connect_slots();
        void print_grid();
        void make_slot(pair<int,int> coord_init, pair<int,int> coord_end, vector<pair<int,int>> dependencies, bool vertical);
        void print_graphviz(const std::string &filename);
        void print_grid_edges();
        void print_grid_edges_graphviz(const std::string &filename);
        
        
        bool fill_grid_r(WordTable *table, Slot *current);
        
        
        int get_most_dependable();
        bool fill_grid_start(WordTable *table, vector<vector<char>> *matrix);
        void print_words();
        
        
        bool choose_word(vector<pair<char, int>>, Slot* current, WordTable* table);
        bool check_dependencies(vector<pair<char,int>> checks, Slot *current, WordTable* table);
    

};