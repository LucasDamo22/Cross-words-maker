#include "./include/Slot.h"

Slot::Slot(){
    coord_init = make_pair(0,0);
    coord_end = make_pair(0,0);
};
Slot::Slot(pair<int, int> coord_init, pair<int, int> coord_end, bool vertical, int id){
    this->coord_init = coord_init;
    this->coord_end  = coord_end;
    this->vertical   = vertical;
    this->id = id;
    this->visited_ = false;
    if(this->vertical){
        this->size = (coord_end.first) - (coord_init.first) + 1;
    } else {
        this->size = (coord_end.second) - (coord_init.second) + 1;
    }
};
Slot::~Slot(){};
pair<int, int> Slot::get_coord_init(){
    return coord_init;
};

pair<int, int> Slot::get_coord_end(){
    return coord_end;
};

vector<pair<Slot*, pair<int, int>>>  Slot::get_edges(){
    return edges;
};

void Slot::add_edge(pair<Slot*, pair<int, int>> edge){
    edges.push_back(edge);
    
}

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

int Slot::get_qt_dependencies(){
    return this->dependencies.size();
}

int Slot::get_size(){
    return this->size;
}


int Slot::get_id(){
    return this->id;
}

int Slot::get_common_position(Slot *slot){
    string word_aux = slot->get_word();
    pair<int,int> coord_init = slot->get_coord_init();
    int aux;
    if(this->vertical){
        aux = coord_init.first - this->coord_init.first;
    } else {
        aux = coord_init.second - this->coord_init.second;
    }
    return aux;
}

char Slot::get_common_char(Slot *slot){
    string word_aux = slot->get_word();
    pair<int,int> coord_init = slot->get_coord_init();
    char aux;
    if(this->vertical){
        aux = word_aux[this->coord_init.second - coord_init.second];
    } else {
        aux = word_aux[this->coord_init.first - coord_init.first];
    }
    return aux;
}

bool Slot::is_vertical(){
    return this->vertical;
}

void Slot::ban_hash(int hash){
    this->banned_hashes.insert(hash);
}

bool Slot::check_bans(int hash){
    return this->banned_hashes.find(hash) != this->banned_hashes.end();
}

bool Slot::visited(){
    return this->visited_;
}

void Slot::set_visited(bool visit){
    this->visited_ = visit;
}