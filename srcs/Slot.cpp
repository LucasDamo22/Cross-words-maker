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
    this->visit = false;
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
    pair<int,int> coord_end = slot->get_coord_end();
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
    pair<int,int> coord_end = slot->get_coord_end();
    char aux;
    if(this->vertical){
        aux = word_aux[this->coord_init.second - coord_init.second];
    } else {
        aux = word_aux[this->coord_init.first - coord_init.first];
    }
    return aux;
}
void Slot::set_visited(bool visit){
    this->visit = visit;
}
bool Slot::visited(){
    return this->visit;
}
bool Slot::is_vertical(){
    return this->vertical;
}

bool Slot::has_word(string word){
    if(this->used_words.find(word) == this->used_words.end()){
        return false;
    }
    return true;
}

void Slot::insert_word(string word){
    this->used_words.insert(word);
}

void Slot::clear_used(){
    this->used_words.clear();
}

int Slot::get_used_words_size(){
    return this->used_words.size();
}