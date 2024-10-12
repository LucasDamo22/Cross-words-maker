#include "./include/main.h"




// ia
//  Function to trim trailing whitespace from a string



int main(){

    pair<int,int> coord_init = make_pair(0,0);
    pair<int,int> coord_end = make_pair(0,0);

    cout<<"Hello From main!"<<std::endl;
    
    vector<string> words;
    unordered_set<string> words_check;
    
    WordTable *table = new WordTable();

    Grid *grid = new Grid();
    
    string file("/home/lucas.damo/Documents/IA/testes/grid-25x25-88W-400L-225B.txt");
    string file_words("testes/lista_palavras.txt");
    vector<string> words_func =  readStringsFromFile("testes/lista_palavras.txt");

    std::ifstream infile(file);
    std::ifstream infile_words(file_words);                     

    // Vector to hold the matrix
    std::vector<std::vector<char>> matrix;
    std::string line;


    /* AI SMALL SECTION */
    while (std::getline(infile, line)) {
        std::vector<char> row(line.begin(), line.end());
        matrix.push_back(row);
    }
    /* AI SMALL SECTION */

    infile.close();
    grid->create_grid(matrix);
    grid->connect_slots();
    grid->print_grid_edges();
    grid->print_grid_edges_graphviz("graph.dot");

    int k = 0;

    int count = 0;
    for(int i =0 ; i < words_func.size(); i++ ){
        if(!already_exists(words_check, words_func[i])){
            table->add_word_p(&words_func[i]);
            count++;
        }
    }

    grid->fill_grid(table);


    delete table;
    delete grid;
 
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

//ia
bool already_exists(unordered_set<string> &words_check, string word){
    if(words_check.find(word) != words_check.end()){
        return true;
    }
    words_check.insert(word);
    return false;
}

