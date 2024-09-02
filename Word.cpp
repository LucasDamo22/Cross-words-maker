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
    // cout<<"====================="<<endl;
    // cout<<std::hex<<c<<endl;
    c = int(c);
    // cout<<std::hex<<c<<endl;
    // cout<<"====================="<<endl;
    
    int hashfinal = (c << 24) | (index << 16) | (size);
    return hashfinal;
};

void WordTable::add_word(string word){
    for(int i = 0; i < word.length(); i++){
        int hash = charHash(word[i],i,word.length());
        //cout<<std::hex<<hash<<" "<< word[i]<<" "<< i <<" "<< word.length()<<endl;
        map[hash].push_back(word);
    }
};

vector<string> WordTable::get_words(char c, int index, int size){
    int hash = charHash(c,index,size);
    return map[hash];
};