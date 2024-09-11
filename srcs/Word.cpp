#include "Word.h"

WordTable::WordTable(){

};

WordTable::~WordTable(){

};

int WordTable::charHash(char c, int index, int size){
    
    index &= ~0xFFFFFF00;
    size &= ~0xFFFF0000;

    c = int(c);

    int hashfinal = (c << 24) | (index << 16) | (size);
    return hashfinal;
};
int WordTable::charHash_p(char *c, int index, int size){
    
    index &= ~0xFFFFFF00;
    size &= ~0xFFFF0000;

    *c = int(*c);

    int hashfinal = (*c << 24) | (index << 16) | (size);
    return hashfinal;
};

void WordTable::add_word(string word){
    for(int i = 0; i < word.length(); i++){
        int hash = charHash(word[i],i,word.length());
        //cout<<std::hex<<hash<<" "<< word[i]<<" "<< i <<" "<< word.length()<<endl;
        map[hash].push_back(word);
    }
};
void WordTable::add_word_p(string *word){
    string cp = *word;
    for(int i = 0; i < word->length(); i++){
        int hash = charHash_p(&cp[i],i,word->length());
        //cout<<std::hex<<hash<<" "<< word[i]<<" "<< i <<" "<< word.length()<<endl;
        map_p[hash].push_back(word);
    }
};

vector<string> WordTable::get_words(char c, int index, int size){
    int hash = charHash(c,index,size);
    if(map[hash].size() == 0){
        cout<<"No words found"<<endl;
    }
    return map[hash];
};

vector<string* > WordTable::get_words_p(char c, int index, int size){
    int hash = charHash(c,index,size);
    if(map_p[hash].size() == 0){
        cout<<"No words found"<<endl;
    }
    return map_p[hash];
};
