#include <iostream>
#include <utility>
#include <unordered_map>
#include <iterator>
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
    string casa = "casa";
    string bala = "bala";
    
    table->add_word(casa);
    table->add_word(bala);
    cout<<"====================="<<endl;
    std::vector<string> words = table->get_words('c',0,4);
    for(int i = 0; i < words.size(); i++){
        cout<<words[i]<<endl;
    }
    cout<<"====================="<<endl;
    words = table->get_words('a',1,4);
    for(int i = 0; i < words.size(); i++){
        cout<<words[i]<<endl;
    }

    
    
   
}

