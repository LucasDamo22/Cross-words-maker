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

//#include "./include/Slot.h"
#include "./include/Word.h"
#include "./include/Grid.h"
using std::unordered_set;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

// ia
//  Function to trim trailing whitespace from a string
std::vector<std::string> readStringsFromFile(const std::string& filename) {
    std::vector<std::string> result;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        result.push_back(line);
    }

    file.close();
    return result;
}
std::string trim_trailing_whitespace(const std::string &str)
{
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
    slot_teste = new Slot(coord_init, coord_end, false);
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
    vector<string> words_func =  readStringsFromFile("testes/palavras_short.txt");

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
    grid->connect_slots();
    //grid->print_graphviz("graph.dot");
    grid->print_grid_edges();
    grid->print_grid_edges_graphviz("graph.dot");

    int k = 0;

    

    // words.push_back("casa");
    // words.push_back("bala");
    // for(int i = 0; i < words.size(); i++){
    //     if (!already_exists(words_check, words[i])){
    //         table->add_word_p(&words[i]);
    //     }
    // }
    // vector<string*> string_pointer = table->get_words_p('a', 1, 4);

    // for(int i = 0; i < string_pointer.size(); i++){
    //     cout<<*string_pointer[i]<<endl;
    // }


    // while (std::getline(infile_words, line))
    // {
    //     line = trim_trailing_whitespace(line);
    //     if (!already_exists(words_check, line))
    //     {
    //         // cout<<line<<endl;
    //         words.push_back(line);
    //         table->add_word_p(&words[words.size() - 1]);
    //     }
    // }

    //TESTE
    // vector<string*> words_tablea = table->get_words_p('a', 1, 4);
    // cout << "Size: " << words_tablea.size() << endl;
    // cout << "Words: " << endl;
    // for (int i = 0; i < words_tablea.size(); i++)
    // {
    //     cout << i << " ";
    //     cout << *words_tablea[i] << endl;
    // }

    for(int i =0 ; i < words_func.size(); i++ ){
        if(!already_exists(words_check, words_func[i])){
            table->add_word_p(&words_func[i]);
        }
    }
    vector<string*> pointers = table->get_words_p('3',1,4);

    for(int i =0; i <pointers.size();i++ ){
        cout<<*pointers[i]<<endl;
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

