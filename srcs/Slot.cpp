#include "./include/Slot.h"

Slot::Slot(){
    coord_init = make_pair(0,0);
    coord_end = make_pair(0,0);
};
Slot::Slot(pair<int, int> coord_init, pair<int, int> coord_end){
    this->coord_init = coord_init;
    this->coord_end = coord_end;
};
Slot::~Slot(){};
pair<int, int> Slot::get_coord_init(){
    return coord_init;
};

pair<int, int> Slot::get_coord_end(){
    return coord_end;
};

vector<Slot*>  Slot::get_edges(){
    return edges;
};

void Slot::add_edge(Slot* edge){
    edges.push_back(edge);
};


vector<pair<int,int>> Slot::get_dependencies(){
    return dependencies;
};

void Slot::add_dependencies(pair<int,int> dependancy){
    dependencies.push_back(dependancy);
};

string Slot::get_word(){
    return word;
};

void Slot::set_word(string word){
    this->word = word;
}