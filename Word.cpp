#include "Word.h"

WordTable::WordTable(){

};

WordTable::~WordTable(){

};

int WordTable::charHash(char c, int index, int size){
    
    index &= ~0xFFFFFF00;
    size &= ~0xFFFF0000;
    //cout<<std::hex<<index<<endl;
    //cout<<std::hex<<size<<endl;
    
    int hashfinal = (c << 24) | (index << 16) | (size);
    return hashfinal;
};