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
                if(!creating_slot && j != matrix[i].size()-1){
                    // CUIDADO COM O MALVADO DO X E Y
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
                    dependencies.clear();
                }
            }else{
                if(creating_slot || (j == matrix[i].size()-1)){
                    if(xstart == i && ystart == j-1){
                        creating_slot = false;
                        continue;
                    }
                    make_slot(make_pair(xstart,ystart),make_pair(i,j-1), dependencies);
                    creating_slot = false;
                    dependencies.clear();
                }
               
            }
        }
    }
};

void Grid::create_grid(vector<vector<char>> matrix){
   horizontal_search(matrix);
};


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