#include <iostream>
#include <utility>
#include <unordered_map>
#include <iterator>
#include <fstream>
//ia
#include <algorithm>  // For std::remove_if and std::isspace
#include <cctype>     // For std::isspace
//ia

#include "Slot.h"
#include "Word.h"
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


int main(){
    cout<<"Hello From main!"<<std::endl;
    Slot *slot_teste;

    vector<string> words;
    words.push_back("casa");
    words.push_back("bala");
    words.push_back("sala");
    pair<int,int> coord_init = make_pair(0,0);
    pair<int,int> coord_end = make_pair(0,0);

    slot_teste = new Slot(coord_init, coord_end);
    WordTable *table = new WordTable();
    string casa = "casa";
    string bala = "bala";
    
    // for(int i = 0 ;i <words.size(); i++){
    //     table->add_word(words[i]);
    // }

    for(int i = 0 ;i <words.size(); i++){
        table->add_word_p(&words[i]);
    }

    vector<string* >strings = table->get_words_p('s', 0, 4);
    
    for(int i = 0; i < strings.size(); i++){
        cout<<*strings[i]<<endl;
    }
    
   
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
    
    std::ifstream infile(file);                     

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

