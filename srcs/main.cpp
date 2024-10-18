#include "./include/main.h"




// ia
//  Function to trim trailing whitespace from a string



int main(int argc, char* argv[]){
    

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    pair<int,int> coord_init = make_pair(0,0);
    pair<int,int> coord_end = make_pair(0,0);

    cout<<"Hello From main!"<<std::endl;
    
    vector<string> words;
    unordered_set<string> words_check;
    
    WordTable *table = new WordTable();

    Grid *grid = new Grid();
    
    string file(argv[1]);
    string file_words("testes/lista_palavras.txt");
    vector<string> words_func =  readStringsFromFile(file_words);

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
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << file << std::endl;
        return 1; // Return an error code or handle the error appropriately
    }

    if (!infile_words.is_open()) {
        std::cerr << "Error: Could not open file " << file_words << std::endl;
        return 1; // Return an error code or handle the error appropriately
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
     

    auto start = std::chrono::high_resolution_clock::now();
    grid->fill_grid_start(table, &matrix);
    auto end = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout<<matrix[i][j];
        }
        cout<<endl;
    }

    //std::cout << "Most dependable slot: " << grid->get_most_dependable() << std::endl;
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;


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

