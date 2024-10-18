#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::pair;
using std::vector;
using std::make_pair;
using std::string;
class Slot{
        unordered_set<string> used_words;
        string                word;
        int                   id;
        bool                  vertical;
        bool                  visit;
        int                   size;
        pair<int, int>        coord_init;   
        pair<int, int>        coord_end;
        vector<pair<Slot*, pair<int, int>>> edges;
        vector<pair<int, int>> dependencies;
        
    public:
        Slot();
        Slot(pair<int, int> coord_init, pair<int, int> coord_end, bool vertical, int id);
        ~Slot();

        pair<int, int> get_coord_init();
        pair<int, int>  get_coord_end();
        
        string get_word();
        
        void set_word(string word);

        void add_edge(pair<Slot*, pair<int, int>> edge);
        vector<pair<Slot*, pair<int, int>>> get_edges();
        int get_qt_dependencies();

        void add_dependencies(pair<int,int>);
        vector<pair<int,int>> get_dependencies();
        int get_size();
        int get_id();
        int get_common_position(Slot *slot);
        char get_common_char(Slot *slot);
        bool is_vertical();
        void set_visited(bool visit);
        bool visited();
        bool has_word(string word);
        void clear_used();
        void insert_word(string word);
        int get_used_words_size();
  
};