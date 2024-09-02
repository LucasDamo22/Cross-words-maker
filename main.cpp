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
    
    std::unordered_map<int, vector<string>> map;
    // for(int i = 0; i < casa.length(); i++){

    //     int hash = table->charHash(casa[i],i,casa.length());
    //     cout<<std::hex<<hash<<" "<< casa[i]<<" "<< i <<" "<< casa.length()<<endl;
    //     map[hash] = casa;
    // }
    // for(int i = 0; i < bala.length(); i++){
    //     int hash = table->charHash(bala[i],i,bala.length());
    //     cout<<std::hex<<hash<<" "<< bala[i]<<" "<< i <<" "<< bala.length()<<endl;
    //     map[hash] = bala;
    // }
    for(int i = 0; i < casa.length(); i++){

        int hash = table->charHash(casa[i],i,casa.length());
        cout<<std::hex<<hash<<" "<< casa[i]<<" "<< i <<" "<< casa.length()<<endl;
        map[hash].push_back(casa);
    }
    for(int i = 0; i < bala.length(); i++){
        int hash = table->charHash(bala[i],i,bala.length());
        cout<<std::hex<<hash<<" "<< bala[i]<<" "<< i <<" "<< bala.length()<<endl;
        map[hash].push_back(bala);
    }
    
    vector<string> casa_vector = map[table->charHash('c',0,4)];

    for(int i = 0; i < casa_vector.size(); i++){
        cout<<casa_vector[i]<<endl;
    }
}

