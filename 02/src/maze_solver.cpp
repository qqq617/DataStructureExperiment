#include"LinkedStack.hpp"
#include<iostream>
#include<vector>
#include<stdexcept>

using namespace std;

struct Position{
    int x;
    int y;
};

bool inMaze(Position p,int L,int W){
    if(p.x < L && p.y < W && p.x >= 0 && p.y >= 0) return true;
    return false;
}

void showPath(LinkedStack<Position>& stack){
    LinkedStack<Position> tmp;
    while(!stack.empty()){
        tmp.push(stack.top());
        stack.pop();
    }
    cout<<"Path:"<<endl;
    while(!tmp.empty()){
        Position p = tmp.top();
        cout<<"(" << p.x << "," << p.y << ")" << endl;
        tmp.pop();
    }
}

bool maze_solver(const vector<vector<int>>& maze){
    if(maze.empty() || maze[0].empty()){
        throw invalid_argument("ERROR: maze is empty.");
    }
    const int Length = maze.size();
    const int Width = maze[0].size();
    for(const auto& row : maze){
        if(row.size() != static_cast<size_t>(Width)) {
            throw invalid_argument("Invalid maze shape");
        }
    }
    if(maze[0][0] != 0 || maze[Length-1][Width-1] != 0){
        return false;
    }

    LinkedStack<Position> stack;
    Position start = {0,0};
    Position end = {Length-1,Width-1};
    stack.push(start);

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1}; 

    vector<vector<bool>> visited(Length, vector<bool>(Width, false));
    visited[0][0] = true;
    
    while(!stack.empty()){
        Position current = stack.top();

        if(current.x == end.x && current.y == end.y){
            showPath(stack);
            return true;
        }
        
        bool found = false;

        for(int i = 0; i < 4; i++){
            Position newP = {current.x + dr[i], current.y + dc[i]};

            if(inMaze(newP,Length,Width) && maze[newP.x][newP.y] == 0 && !visited[newP.x][newP.y]){
                stack.push(newP);
                found = true;
                visited[newP.x][newP.y] = true;
                break;
            }
        }
        
        if(!found) stack.pop();
    }
    cout<< "There is no path" <<endl;
    return false;
}