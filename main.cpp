#include <QCoreApplication>
#include <iostream>
#include <vector>
using namespace std;
int my_x = 1;
int my_y = 4;
int goal_x = 5;
int goal_y = 0;
char my_map[5][6] = {
{' ','#',' ',' ',' ',' '},
{'#',' ',' ','#','#','#'},
{' ',' ',' ',' ',' ',' '},
{' ','#','#','#','#',' '},
{' ',' ',' ',' ',' ',' '}
};
struct node{
    int x;
    int y;
    vector<pair<int,int> > path;
};
vector<node> visited;
vector<node> open_list;
void add_node(node cur);
bool is_node_valid(node tmp);
bool is_node_in_field(node tmp);
bool is_node_in_visited(node tmp);
bool is_wall(node tmp);
bool is_final(node tmp);
node get_best_node();
double calc_node_error(node tmp);
int main()
{
    node cur_node;
    cur_node.x = my_x;
    cur_node.y = my_y;
    open_list.push_back(cur_node);

    cout << "nodes got open in order : "<<endl;
    while(!open_list.empty()){
        cur_node = get_best_node();

        cout << cur_node.x << " , " << cur_node.y << endl;

        visited.push_back(cur_node);
        if(is_final(cur_node)){
            break;
        }
        add_node(cur_node);
    }
    cout << "path :"<<endl;
    for(int i = 0 ; i < cur_node.path.size() ; i++){
        cout << cur_node.path.at(i).first << " , "<< cur_node.path.at(i).second << endl;
    }


    return 0;
}
double calc_node_error(node tmp){
    double error = abs(tmp.x - goal_x) + abs(tmp.y - goal_y);
    return error;
}
node get_best_node(){
    double min_error = 9999;
    double best_node_index;
    for(int i = 0 ; i < open_list.size() ; i++){
        node tmp = open_list.at(i);
        double cur_node_error = calc_node_error(tmp);
        if(cur_node_error < min_error){
            min_error = cur_node_error;
            best_node_index = i;
        }
    }
    node best_node = open_list.at(best_node_index);
    open_list.erase(open_list.begin() + best_node_index);
    return best_node;
}
bool is_final(node tmp){
    if(tmp.x == goal_x && tmp.y == goal_y){
        return true;
    }
    return false;
}
void add_node(node cur){
    vector <pair<int,int> > new_path = cur.path;
    pair<int,int> head_node;
    head_node.first = cur.x;
    head_node.second= cur.y;

    node t1 = cur;
    t1.x -= 1;
    t1.path.push_back(head_node);
    if(is_node_valid(t1)){
        open_list.push_back(t1);
    }

    node t2 = cur;
    t2.x += 1;
    t2.path.push_back(head_node);
    if(is_node_valid(t2)){
        open_list.push_back(t2);
    }

    node t3 = cur;
    t3.y -= 1;
    t3.path.push_back(head_node);
    if(is_node_valid(t3)){
        open_list.push_back(t3);
    }

    node t4 = cur;
    t4.y += 1;
    t4.path.push_back(head_node);
    if(is_node_valid(t4)){
        open_list.push_back(t4);
    }

}
bool is_node_valid(node tmp){
    if(is_node_in_field(tmp) == false){
        return false;
    }
    if(is_node_in_visited(tmp)){
        return false;
    }
    if(is_wall(tmp)){
        return false;
    }
    return true;
}
bool is_node_in_field(node tmp){
    if(tmp.x <0 || tmp.y < 0){
        return false;
    }
    if(tmp.x > 5){
        return false;
    }
    if(tmp.y > 4){
        return false;
    }
    return true;
}
bool is_node_in_visited(node tmp){
    for(int i = 0 ; i < visited.size() ; i++){
        if(visited.at(i).x == tmp.x && visited.at(i).y == tmp.y){
            return true;
        }
    }
    return false;
}
bool is_wall(node tmp){
    if(my_map[tmp.y][tmp.x] == '#'){
        return true;
    }
    return false;
}






