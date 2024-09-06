#include "Grid.h"


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
void Grid::horizontal_search(vector<vector<char>> &matrix){
    int xstart = 0;
    int ystart = 0;
    vector<pair<int,int>> dependencies;
    bool creating_slot = false;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j]=='?'){
                if(!creating_slot){
                    xstart = j;
                    ystart = i;
                    creating_slot = true;
                }
                if(matrix[i][j+1] == '?'){
                    dependencies.push_back(make_pair(i,j));
                }
                if(matrix[i][j-1] == '?'){
                    dependencies.push_back(make_pair(i,j));
                }
            }else{
                if(creating_slot || (j == matrix[i].size()-1)){
                    if(xstart == i-1 && ystart == j-1){
                        creating_slot = false;
                        continue;
                    }
                    Slot slot(make_pair(ystart,xstart),make_pair(i,j));
                    for(int k = 0; k < dependencies.size(); k++){
                        slot.add_dependancies(dependencies[k]);
                    }
                    add_slot(slot);
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
        std::cout<<"Slot "<<i<<": "<<coord_init.first<<","<<coord_init.second<<" "<<coord_end.first<<","<<coord_end.second<<std::endl;
    }
};