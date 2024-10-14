#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <tuple>
#include <algorithm>
#include "Slot.h"
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
        vector<string*> used_words;
        int more_dependable;
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
        void fill_grid(WordTable *table);
        bool fill_grid_r(WordTable *table, Slot *current);
        bool fill_grid_r_2(WordTable *table, Slot *current, vector<Slot*> stack);
        int get_most_dependable();
        bool fill_grid_start(WordTable *table, vector<vector<char>> *matrix);
        void print_words();
        string* find_word(vector<string*> words, vector<pair<char, int>> cells, Slot *current);
        string* find_string_ref(string str);
    

};