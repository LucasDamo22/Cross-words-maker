#include "./include/Grid.h"


Grid::Grid(){
    
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

Slot Grid::make_slot(pair<int,int> coord_init, pair<int,int> coord_end, vector<pair<int,int>> dependencies){
    Slot new_slot(coord_init,coord_end);
    for(int k = 0; k < dependencies.size(); k++){
        new_slot.add_dependencies(dependencies[k]);
    }

    add_slot(new_slot);
    return new_slot;
};


void Grid::horizontal_search(vector<vector<char>> &matrix){
    int xstart = 0;
    int ystart = 0;
    vector<pair<int,int>> dependencies;
    bool creating_slot = false;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j]=='?'){
                if(!creating_slot && j < matrix[i].size()-1){
                    // CUIDADO COM O MALVADO DO X E Y
                    dependencies.clear();
                    xstart = i;
                    ystart = j;
                    creating_slot = true;
                }
                if(i == matrix.size()-1){                          // making sure we are not out of bounds
                    if(matrix[i-1][j] == '?'){
                        dependencies.push_back(make_pair(i,j));
                    }
                }else if(i == 0){                                  // making sure we are not out of bounds
                    if(matrix[i+1][j] == '?'){
                        dependencies.push_back(make_pair(i,j));
                    }
                }else{                                             // all the other cases (inbounds)
                    if(matrix[i+1][j] == '?' || matrix[i-1][j] == '?'){
                        dependencies.push_back(make_pair(i,j));
                    }
                }
                if(j == matrix[i].size()-1 && creating_slot){
                    make_slot(make_pair(xstart,ystart),make_pair(i,j), dependencies);
                    creating_slot = false;
                }
            }else{
                if(creating_slot || (j == matrix[i].size()-1)){
                    if(xstart == i && ystart == j-1){
                        creating_slot = false;
                        continue;
                    }
                    make_slot(make_pair(xstart,ystart),make_pair(i,j-1), dependencies);
                    creating_slot = false;
                }
            }
        }
    }
};

void Grid::vertical_search(vector<vector<char>> &matrix) {
    int xstart = 0;
    int ystart = 0;
    vector<pair<int, int>> dependencies;
    bool creating_slot = false;

    for (int j = 0; j < matrix[0].size(); j++) { // Iterate over columns first
        for (int i = 0; i < matrix.size(); i++) { // Then iterate over rows
            if (matrix[i][j] == '?') {
                if (!creating_slot && i < matrix.size() - 1) {
                    dependencies.clear();
                    xstart = i;
                    ystart = j;
                    creating_slot = true;
                }
                if (j == matrix[0].size() - 1) { // making sure we are not out of bounds
                    if (matrix[i][j - 1] == '?') {
                        dependencies.push_back(make_pair(i, j));
                    }
                } else if (j == 0) { // making sure we are not out of bounds
                    if (matrix[i][j + 1] == '?') {
                        dependencies.push_back(make_pair(i, j));
                    }
                } else { // all the other cases (inbounds)
                    if (matrix[i][j + 1] == '?' || matrix[i][j - 1] == '?') {
                        dependencies.push_back(make_pair(i, j));
                    }
                }
                if (i == matrix.size() - 1 && creating_slot) {
                    make_slot(make_pair(xstart, ystart), make_pair(i, j), dependencies);
                    creating_slot = false;
                }
            } else {
                if (creating_slot || (i == matrix.size() - 1)) {
                    if (xstart == i - 1 && ystart == j) {
                        creating_slot = false;
                        continue;
                    }
                    make_slot(make_pair(xstart, ystart), make_pair(i - 1, j), dependencies);
                    creating_slot = false;
                }
            }
        }
    }
};

void Grid::create_grid(vector<vector<char>> matrix){
   horizontal_search(matrix);
   vertical_search(matrix);
};

pair<int,int> equal_pairs(vector<pair<int, int>> &dep_a, vector<pair<int, int>> &dep_b){
    //cout<<dep_a[0].first<<dep_a[0].second<<"kek"<<endl;
    
    for (const auto &pair_i : dep_a) {
                for (const auto &pair_j : dep_b) {
                    if (pair_i == pair_j) {
                        //cout<<"pares enguais "<<pair_i.first<<" "<<pair_i.second<<"|"<<pair_j.first<<" "<< pair_i.second<<endl;
                        return pair_i;                       
                    }
                }
            }
    
    return make_pair(-1, -1);
}

void Grid::connect_slots(){
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
    }
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

void Grid::print_grid(){
    for(int i = 0; i < slots.size(); i++){
        pair<int,int> coord_init = slots[i].get_coord_init();
        pair<int,int> coord_end = slots[i].get_coord_end();
        std::cout<<"Slot "<<i<<": "<<coord_init.first<<","<<coord_init.second<<" "<<coord_end.first<<","<<coord_end.second;
        for(int j = 0; j < slots[i].get_dependencies().size(); j++){
            std::cout<<" "<<slots[i].get_dependencies()[j].first<<","<<slots[i].get_dependencies()[j].second;
        }
        std::cout<<std::endl;
    }
};
void Grid::print_grid_edges(){
    for(int i =0; i < slots.size(); i++){
        pair<int,int> coord_init = slots[i].get_coord_init();
        pair<int,int> coord_end = slots[i].get_coord_end();
        std::cout<<"Slot "<<i<<": "<<coord_init.first<<","<<coord_init.second<<" "<<coord_end.first<<","<<coord_end.second<<"  ";;
        //cout<<"SIZE DOQ EU QUERO"<<slots[i].get_edges().size()<<endl;
        for(int j=0; j < slots[i].get_edges().size(); j++){
            pair<Slot*, pair<int,int>> pairAux = slots[i].get_edges()[j];
            Slot* slotAux = pairAux.first;
            pair<int,int> pairAux2 = pairAux.second;
            cout << "Edge to: (" << slotAux->get_coord_init().first<<"," <<slotAux->get_coord_init().second << ")(" <<slotAux->get_coord_end().first<<","<<slotAux->get_coord_end().second<< ") Dependency: (" << pairAux2.first <<"," << pairAux2.second<<")";
        }
        cout<<endl;
    }
}
void Grid::print_grid_edges_graphviz(const std::string &filename) {
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
        file << "    slot" << i << " [label=\"{" << coord_init.first << "," << coord_init.second << " " << coord_end.first << "," << coord_end.second << "}\"];" << std::endl;
    }

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
                file << "    slot" << i << " -> slot" << slotAuxIndex << " [label=\"(" << pairAux2.first << "," << pairAux2.second << ")\"];" << std::endl;
            }
        }
    }

    file << "}" << std::endl;
    file.close();
    std::cout << "Graphviz file " << filename << " generated successfully." << std::endl;
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