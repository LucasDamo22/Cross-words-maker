#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include "Slot.h"
using std::pair;
using std::vector;
using std::string;

class Grid{
    public:
        Grid();
        
        ~Grid();
        void add_slot(Slot slot);
        void create_grid(vector<vector<char>> matrix);
        void horizontal_search(vector<vector<char>> &matrix);
        void vertical_search(vector<vector<char>> &matrix);
        vector<Slot*> get_slots();
        void connect_slots();
        void print_grid();

    vector<Slot> slots;



};