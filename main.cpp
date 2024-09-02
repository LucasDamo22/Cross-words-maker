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


    cout<< slot_teste->get_coord_init().first << " " << slot_teste->get_coord_init().second << endl;
    cout<< slot_teste->get_coord_end().first << " " << slot_teste->get_coord_end().second << endl;
    //cout<< std::hex << table->charHash('b',1,4) << endl;
    string casa = "casa";
    string bala = "bala";
    


    std::unordered_map<int, string> map;
    for(int i = 0; i < casa.length(); i++){
        int hash = table->charHash(casa[i],i,casa.length());
        cout<<hash<< casa[i]<<endl;
        map[hash] = casa;
    }
    for(int i = 0; i < bala.length(); i++){
        map[table->charHash(bala[i],i,bala.length())] = bala;
    }
    int target = table->charHash('c',0,4);
    cout<<target<<endl;
    size_t bucket_count = map.bucket_count();
    cout<<"bucket_count: "<<bucket_count<<endl;

    size_t bucket = map.bucket(target);

    size_t bucket_size = map.bucket_size(bucket);
    cout<<"bucket_size: "<<bucket_size<<endl;

    cout<<"bucket: "<<bucket<<endl;

    
    
    
    
      
    
    


}

