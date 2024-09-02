#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>

using std::pair;
using std::vector;
using std::make_pair;
using std::string;
class Slot{
        string                word;
        int                   size;
        pair<int, int>        coord_init;   
        pair<int, int>        coord_end;
        vector<Slot*>         edges;
        vector<pair<int, int>> dependancies;
        
        //vector<pair<Slot*,pair<int, int>>> dependancies

    public:
        Slot();
        Slot(pair<int, int> coord_init, pair<int, int> coord_end);
        ~Slot();

        pair<int, int> get_coord_init();
        pair<int, int>  get_coord_end();
        
        string get_word();
        
        void set_word(string word);

        void add_edge(Slot* edge);
        vector<Slot*> get_edges();

        void add_dependancies(pair<int,int>);
        vector<pair<int,int>> get_dependancies();
};