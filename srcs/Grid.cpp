#include "./include/Grid.h"


Grid::Grid(){
    more_dependable = 0;
};
Grid::~Grid(){
    
};
void Grid::add_slot(Slot slot){
    slots.push_back(slot);
};

vector<Slot*> Grid::get_slots(){
    vector<Slot*> slot_p;
    for(int i = 0; i < slots.size(); i++){
        slot_p.push_back(&slots[i]);
    }
    return slot_p;
};

void Grid::make_slot(pair<int,int> coord_init, pair<int,int> coord_end, vector<pair<int,int>> dependencies, bool vertical){
    
    int new_id = slots.size() + 1;
    Slot new_slot(coord_init,coord_end, vertical, new_id);

    for(int k = 0; k < dependencies.size(); k++){
        new_slot.add_dependencies(dependencies[k]);
    }

    add_slot(new_slot);
};


void Grid::horizontal_search_2(vector<vector<char>> &matrix){

    vector<pair<int, int>> dependencies;
    bool creating_slot = false;
    int xstart;
    int ystart;

    for(int y = 0; y < matrix.size(); y++){
        for(int x = 0; x < matrix[y].size(); x++){
            if(matrix[y][x] == '?'){
                if(!creating_slot){
                    dependencies.clear();
                    creating_slot = true;
                    xstart = x;
                    ystart = y;
                }
                // dependence check
                // if on the first line
                if(0 == y){
                    if(matrix[y+1][x] == '?'){
                        dependencies.push_back(make_pair(y,x));
                    }
                } 
                // if on the last line
                else if ((matrix.size() - 1) == y){
                    if(matrix[y-1][x] == '?'){
                        dependencies.push_back(make_pair(y,x));
                    }
                // all the other lines
                }else{
                    if((matrix[y-1][x] == '?') || (matrix[y+1][x] == '?')){
                        dependencies.push_back(make_pair(y,x));
                    }
                }
                // dependence check end*/

                // EOL CHECK
                if(x == (matrix[y].size() - 1)){ // checking if we are on the last char of the line
                    if(creating_slot){
                        if(xstart != (x)){
                            make_slot(make_pair(ystart, xstart), make_pair(y, x), dependencies, false);
                        }
                        dependencies.clear();
                        xstart = 0;
                        ystart = 0;
                        creating_slot = false;
                    }
                }
                // EOL CHECK END
            } else {
                // only one ?  doesnt form word
                if(creating_slot){
                    if(xstart != (x -1)){
                        make_slot(make_pair(ystart, xstart), make_pair(y, (x-1)), dependencies, false);
                    }
                    dependencies.clear();
                    xstart = 0;
                    ystart = 0;
                    creating_slot = false;
                }
            }
        }
    }
}

void Grid::vertical_search_2(vector<vector<char>> &matrix){
    vector<pair<int, int>> dependencies;
    bool creating_slot = false;
    int xstart;
    int ystart;
    for(int x = 0; x < matrix[0].size(); x++){
        for(int y = 0; y < matrix.size(); y++){
            if(matrix[y][x]== '?'){
                if(!creating_slot){
                    creating_slot = true;
                    xstart = x;
                    ystart = y;
                    dependencies.clear();
                }
                if(0 == x){
                    if(matrix[y][x+1] == '?'){
                        dependencies.push_back(make_pair(y, x));
                    }
                }
                else if((matrix[y].size() - 1) == x){
                    if(matrix[y][x-1] == '?'){
                        dependencies.push_back(make_pair(y, x));
                    }
                }
                else {
                    if((matrix[y][x+1] == '?')||(matrix[y][x-1] == '?')){
                        dependencies.push_back(make_pair(y, x));
                    }
                }

                if( y == (matrix.size() - 1)){
                    if(creating_slot){
                        if(ystart != y){
                            make_slot(make_pair(ystart, xstart), make_pair(y, x), dependencies, true);
                        }
                        dependencies.clear();
                        xstart = 0;
                        ystart = 0;
                        creating_slot = false;
                    }
                }
            } else {
                if(creating_slot){
                    if (ystart != (y - 1)){
                        make_slot(make_pair(ystart, xstart), make_pair((y-1), x), dependencies, true);
                    }
                    dependencies.clear();
                    xstart = 0;
                    ystart = 0;
                    creating_slot = false;
                }
            }
        }
    }
};




void Grid::create_grid(vector<vector<char>> matrix){
   horizontal_search_2(matrix);
   vertical_search_2(matrix);
};

pair<int,int> equal_pairs(vector<pair<int, int>> &dep_a, vector<pair<int, int>> &dep_b){
    for (const auto &pair_i : dep_a) {
                for (const auto &pair_j : dep_b) {
                    if (pair_i == pair_j) {
                        return pair_i;                       
                    }
                }
            }
    return make_pair(-1, -1);
}

void Grid::connect_slots(){
    int aux = 0;
    for(int i = 0; i < slots.size(); i++){
        vector<pair<int, int>> dep_i = slots[i].get_dependencies();
        for(int j = i+1; j < slots.size(); j++){
            vector<pair<int, int>> dep_j = slots[j].get_dependencies();
            pair<int,int> equal = equal_pairs(dep_i, dep_j);
            if(equal != make_pair(-1,-1)){
                slots[i].add_edge(make_pair(&slots[j],equal));
                slots[j].add_edge(make_pair(&slots[i],equal));
            }
        }
        if(slots[i].get_qt_dependencies() > aux){
            more_dependable = i;
            aux = slots[i].get_qt_dependencies();
        }
    }
}

void Grid::print_grid_edges(){
    for(int i =0; i < slots.size(); i++){
        pair<int,int> coord_init = slots[i].get_coord_init();
        pair<int,int> coord_end = slots[i].get_coord_end();
        std::cout<<"Slot "<<slots[i].get_id()<<": ("<<coord_init.first<<","<<coord_init.second<<") - ("<<coord_end.first<<","<<coord_end.second<<")  ";
        cout << "Edge to: ";
        for(int j=0; j < slots[i].get_edges().size(); j++){
            pair<Slot*, pair<int,int>> pairAux = slots[i].get_edges()[j];
            Slot* slotAux = pairAux.first;
            pair<int,int> pairAux2 = pairAux.second;
            cout << "(" <<slotAux->get_id() << ") ";
        }
        cout << endl;
    }
}
bool already_exists_fill(unordered_set<string> &words_check, string word){
    if(words_check.find(word) != words_check.end()){
        return true;
    }
    words_check.insert(word);
    return false;
}


bool Grid::fill_grid_start(WordTable *table, vector<vector<char>> *matrix){
    Slot *most_dependable = &slots[more_dependable];
    unordered_set<string> used_words;
    vector<pair<Slot *, pair<int,int>>> queue;
    vector<Slot *> stack;
    Slot *current = most_dependable;
    vector<string *> words = table->get_words_bysize(current->get_size());
    int i = 0;
    bool done = false;
    while(!done){
        if(!fill_grid_r(table, current)){
            current->set_visited(false);
        }else{
            done = true;
        }
    }
    
    print_words();

    for(int i = 0; i < slots.size(); i++){
        pair<int,int> coord_init = slots[i].get_coord_init();
        pair<int,int> coord_end = slots[i].get_coord_end();
        for(int j = 0; j < slots[i].get_word().size(); j++){
            if(slots[i].is_vertical()){
                (*matrix)[coord_init.first + j][coord_init.second] = slots[i].get_word().at(j);
            } else {
                (*matrix)[coord_init.first][coord_init.second + j] = slots[i].get_word().at(j);
            }
        }
    }
    return true;
}

string* Grid::find_word(vector<string*> words, vector<pair<char, int>> cells, Slot *current) {
    if (cells.size() == 0) {
        for(int i = 0; i < words.size(); i++){
            if(!current->has_word(*words[i])){
                this->used_words.push_back(words[i]);
                current->insert_word(*words[i]);
                return words[i];
            }
        }
        //cout << "sem cells e sem mais words" << endl;
        return nullptr;
    }

    for (int i = 0; i < words.size(); i++) {
        if (current->has_word(*words[i])) {
            continue; // Skip already used words
        }

        for (int j = 0; j < cells.size(); j++) {
            if (words[i]->at(cells[j].second) != cells[j].first) {
                break;
            } else if (j == cells.size() - 1) {
                current->insert_word(*words[i]);
                this->used_words.push_back(words[i]);
                return words[i];
            }
        }
    }
    //cout<<"nao achou nenhuma compativel;"<<endl;
    return nullptr;
}
bool Grid::fill_grid_r_2(WordTable *table, Slot *current, vector<Slot*> stack){
    vector<string*> words = table->get_words_bysize(current->get_size());
    vector<pair<Slot*, pair<int,int>>> edges = current->get_edges();
    vector<pair<char, int>> checks;
    string *word;
    string hold;
    int index_current;
    int index_edge;
    print_words();
    //cout << "SLOT ATUAL: " << current->get_id() << " (" << current->get_coord_init().first << "," << current->get_coord_init().second << ") (" << current->get_coord_end().first << "," << current->get_coord_end().second << ")" << endl;
    for(int i = 0; i < this->used_words.size(); i++){
        words.erase(std::remove(words.begin(), words.end(), this->used_words[i]), words.end());
    }

    //stack.push_back(current);
    
    if(current->get_word() == ""){
        bool done = false;
        while(!done){
            for(int i = 0; i < edges.size(); i++){
                if(current->is_vertical()){
                        index_current = edges[i].second.first - current->get_coord_init().first;
                    } else {
                        index_current = edges[i].second.second - current->get_coord_init().second;
                    }
                    index_edge = edges[i].first->get_common_position(current);
                    if(edges[i].first->get_word() != ""){
                        checks.push_back(make_pair(char(edges[i].first->get_word().at(index_edge)), index_current));
                }
            }
            word = find_word(words, checks, current);
            if(word == nullptr){
                stack.pop_back();
                current->set_word("");
                return false;
            }
            current->set_word(*word);
            bool break_loop = true;
            for(int i  = 0; i < edges.size(); i ++){
                if(!fill_grid_r_2(table, edges[i].first, stack)){
                    for(int j = 0; j < i; j++){
                        /*nao remove palavras ja colocadas anteriormente*/
                       if(!(find(stack.begin(), stack.end(), edges[j].first) !=stack.end())){
                            edges[j].first->clear_used();
                            edges[j].first->set_word("");
                        }
                    }
                    break_loop = false;
                    break;
                }
            }
            if(break_loop){
                done = true;
            }
        }
    }
    return true;
}






string* Grid::find_string_ref(string str){
     for (const auto& word_ptr : used_words) {
        if (*word_ptr == str) {
            return word_ptr;
        }
    }
    return nullptr;
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

// void Grid::print_in_matrix(){

// }

void Grid::print_grid(){
    for(int i = 0; i < slots.size(); i++){
        pair<int,int> coord_init = slots[i].get_coord_init();
        pair<int,int> coord_end = slots[i].get_coord_end();
        std::cout<<"Slot "<<slots[i].get_id()<<": "<<coord_init.first<<","<<coord_init.second<<" "<<coord_end.first<<","<<coord_end.second;
        for(int j = 0; j < slots[i].get_dependencies().size(); j++){
            std::cout<<" "<<slots[i].get_dependencies()[j].first<<","<<slots[i].get_dependencies()[j].second;
        }
        std::cout<<std::endl;
    }
};

struct tuple_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::tuple<T1, T2> &tuple) const {
        auto h1 = std::hash<T1>{}(std::get<0>(tuple));
        auto h2 = std::hash<T2>{}(std::get<1>(tuple));
        return h1 ^ h2;
    }
};
void Grid::print_grid_edges_graphviz(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file << "digraph G {" << std::endl;
    file << "    node [shape=ellipse];" << std::endl; // Change node shape to ellipse
    file << "    layout=circo;" << std::endl; // Use circo layout engine
    file << "    overlap=false;" << std::endl; // Reduce node overlap
    file << "    sep=1;" << std::endl; // Add extra space between nodes
    file << "    splines=true;" << std::endl; // Use curved edges

    int num_slots = slots.size();

    // Print nodes without fixed positions
    for (int i = 0; i < num_slots; i++) {
        pair<int, int> coord_init = slots[i].get_coord_init();
        pair<int, int> coord_end = slots[i].get_coord_end();
        file << "    slot" << i << " [label=\"{" << coord_init.first << "," << coord_init.second << " | " << coord_end.first << "," << coord_end.second << "}\"];" << std::endl;
    }

    // Set to keep track of printed edges
    std::unordered_set<std::tuple<int, int>, tuple_hash> printed_edges;

    // Print edges
    for (int i = 0; i < slots.size(); i++) {
        for (int j = 0; j < slots[i].get_edges().size(); j++) {
            pair<Slot*, pair<int, int>> pairAux = slots[i].get_edges()[j];
            Slot* slotAux = pairAux.first;
            pair<int, int> pairAux2 = pairAux.second;

            // Find the index of the slotAux
            int slotAuxIndex = -1;
            for (int k = 0; k < slots.size(); k++) {
                if (slots[k].get_coord_init() == slotAux->get_coord_init() && slots[k].get_coord_end() == slotAux->get_coord_end()) {
                    slotAuxIndex = k;
                    break;
                }
            }

            if (slotAuxIndex != -1) {
                // Check if the edge or its reverse has already been printed
                auto edge = std::make_tuple(i, slotAuxIndex);
                auto reverse_edge = std::make_tuple(slotAuxIndex, i);
                if (printed_edges.find(reverse_edge) == printed_edges.end()) {
                    // Customize the arrow style here
                    file << "    slot" << i << " -> slot" << slotAuxIndex 
                         << " [label=\"(" << pairAux2.first << "," << pairAux2.second << ")\", "
                         << "color=\"blue\", style=\"solid\", arrowhead=\"diamond\", dir=\"both\", "
                         << "minlen=3];" << std::endl;
                    printed_edges.insert(edge);
                }
            }
        }
    }

    file << "}" << std::endl;
    file.close();
    std::cout << "Graphviz file " << filename << " generated successfully." << std::endl;
}

void Grid::print_words(){
    for(int i = 0; i <slots.size(); i++){
        cout<< "ID DO SLOT "<< slots[i].get_id() << " word :" << slots[i].get_word()<<endl;
    }
    cout<<"==================="<<endl;
}

void Grid::print_graphviz(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file << "digraph G {" << std::endl;
    file << "    node [shape=record];" << std::endl;

    // Print nodes
    for (int i = 0; i < slots.size(); i++) {
        pair<int, int> coord_init = slots[i].get_coord_init();
        pair<int, int> coord_end = slots[i].get_coord_end();
        file << "    slot" << i << " [label=\"{" << coord_init.first << "," << coord_init.second << " | " << coord_end.first << "," << coord_end.second << "}\"];" << std::endl;
    }

    // Print edges for dependencies
    for (int i = 0; i < slots.size(); i++) {
        for (const auto &dep : slots[i].get_dependencies()) {
            for (int j = 0; j < slots.size(); j++) {
                if (slots[j].get_coord_init() == dep) {
                    file << "    slot" << i << " -> slot" << j << ";" << std::endl;
                }
            }
        }
    }

    file << "}" << std::endl;
    file.close();
    std::cout << "Graphviz file " << filename << " generated successfully." << std::endl;
}

int Grid::get_most_dependable(){
    return more_dependable;
}