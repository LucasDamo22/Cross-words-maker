#include <iostream>
#include <utility>
#include "Slot.h"
#include "Word.h"
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
int main(){
    cout<<"Hello From main!"<<std::endl;
    Slot *slot_teste;
    pair<int,int> coord_init = make_pair(0,0);
    pair<int,int> coord_end = make_pair(0,0);

    slot_teste = new Slot(coord_init, coord_end);
    WordTable *table = new WordTable();


    cout<< slot_teste->get_coord_init().first << " " << slot_teste->get_coord_init().second << endl;
    cout<< slot_teste->get_coord_end().first << " " << slot_teste->get_coord_end().second << endl;
    cout<< std::hex << table->charHash('b',1,4) << endl;


}

