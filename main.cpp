#include <iostream>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <fstream>
//ia
#include <algorithm>  // For std::remove_if and std::isspace
#include <cctype>     // For std::isspace
//ia

//#include "Slot.h"
#include "Word.h"
#include "Grid.h"
using std::unordered_set;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

//ia
// Function to trim trailing whitespace from a string
std::string trim_trailing_whitespace(const std::string& str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), [](unsigned char x) {
        return std::isspace(x) && x != ' ';  // Only remove newlines and carriage returns
    }), result.end());
    return result;
}
//ia
bool already_exists(unordered_set<string> &words_check, string word){
    if(words_check.find(word) != words_check.end()){
        return true;
    }
    words_check.insert(word);
    return false;
}


int main(){
    Slot *slot_teste;
    pair<int,int> coord_init = make_pair(0,0);
    pair<int,int> coord_end = make_pair(0,0);
    slot_teste = new Slot(coord_init, coord_end);
    string casa = "casa";
    string bala = "bala";
    

    cout<<"Hello From main!"<<std::endl;
    
    vector<string> words;
    unordered_set<string> words_check;
    
    WordTable *table = new WordTable();

    Grid *grid = new Grid();
    

   
    
   
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//       $$$$$$\  $$$$$$\        $$$$$$\  $$$$$$$$\  $$$$$$\ $$$$$$$$\ $$$$$$\  $$$$$$\  $$\   $$\ 
//      $$  __$$\ \_$$  _|      $$  __$$\ $$  _____|$$  __$$\\__$$  __|\_$$  _|$$  __$$\ $$$\  $$ |
//      $$ /  $$ |  $$ |        $$ /  \__|$$ |      $$ /  \__|  $$ |     $$ |  $$ /  $$ |$$$$\ $$ |
//      $$$$$$$$ |  $$ |        \$$$$$$\  $$$$$\    $$ |        $$ |     $$ |  $$ |  $$ |$$ $$\$$ |
//      $$  __$$ |  $$ |         \____$$\ $$  __|   $$ |        $$ |     $$ |  $$ |  $$ |$$ \$$$$ |
//      $$ |  $$ |  $$ |        $$\   $$ |$$ |      $$ |  $$\   $$ |     $$ |  $$ |  $$ |$$ |\$$$ |
//      $$ |  $$ |$$$$$$\       \$$$$$$  |$$$$$$$$\ \$$$$$$  |  $$ |   $$$$$$\  $$$$$$  |$$ | \$$ |
//      \__|  \__|\______|       \______/ \________| \______/   \__|   \______| \______/ \__|  \__|
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

    string file("testes/grid-11x11-20W-84L-37B.txt");
    string file_words("testes/palavras_short.txt");
    
    std::ifstream infile(file);
    std::ifstream infile_words(file_words);                     

    // Vector to hold the matrix
    std::vector<std::vector<char>> matrix;
    std::string line;

    // Read the file line by line
    while (std::getline(infile, line)) {
        // Trim trailing whitespace (including newlines and carriage returns)
        line = trim_trailing_whitespace(line);

        // Convert the trimmed line into a row of characters
        std::vector<char> row(line.begin(), line.end());

        // Add the row to the matrix
        matrix.push_back(row);
    }

    infile.close();
    grid->create_grid(matrix);

    int k = 0;

    while(std::getline(infile_words, line)){
        line = trim_trailing_whitespace(line);
        if(!already_exists(words_check, line)){
            //cout<<line<<endl;
            words.push_back(line);
            table->add_word_p(&words[words.size()-1]);
        }
    }

     // Display the matrix
    // for (const auto& row : matrix) {
    //     for (char ch : row) {
    //         std::cout << ch;
    //     }
    //     std::cout << std::endl;
    // }

//////////////////////////////////////////////////////////////////////////////////////////////////////  
//
//
//       $$$$$$\  $$$$$$\        $$$$$$\  $$$$$$$$\  $$$$$$\ $$$$$$$$\ $$$$$$\  $$$$$$\  $$\   $$\ 
//      $$  __$$\ \_$$  _|      $$  __$$\ $$  _____|$$  __$$\\__$$  __|\_$$  _|$$  __$$\ $$$\  $$ |
//      $$ /  $$ |  $$ |        $$ /  \__|$$ |      $$ /  \__|  $$ |     $$ |  $$ /  $$ |$$$$\ $$ |
//      $$$$$$$$ |  $$ |        \$$$$$$\  $$$$$\    $$ |        $$ |     $$ |  $$ |  $$ |$$ $$\$$ |
//      $$  __$$ |  $$ |         \____$$\ $$  __|   $$ |        $$ |     $$ |  $$ |  $$ |$$ \$$$$ |
//      $$ |  $$ |  $$ |        $$\   $$ |$$ |      $$ |  $$\   $$ |     $$ |  $$ |  $$ |$$ |\$$$ |
//      $$ |  $$ |$$$$$$\       \$$$$$$  |$$$$$$$$\ \$$$$$$  |  $$ |   $$$$$$\  $$$$$$  |$$ | \$$ |
//      \__|  \__|\______|       \______/ \________| \______/   \__|   \______| \______/ \__|  \__|
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
    // cout<<"=============="<<endl;

    // //finding
    // for(int i = 0; i < matrix.size(); i++){
    //     for(int j = 0;j < matrix[i].size();j++){
    //         if(matrix[i][j] == '?'){
    //             cout<<"a";
    //         }else{
    //             cout<<"b";
    //         }
    //     }
    //     cout<<endl;
    // }

    
    
   
}

