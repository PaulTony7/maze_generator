#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int colls,rows;
bool** maze;
bool** visited;

int MazeAt(const int& arg);
int VisitedAt(const int& arg);

int main() {
//Initiate
    do{
        std::cout << "collumns count: ";
        std::cin >> colls;
        std::cout << "row count: ";
        std::cin >> rows; 
    }while( rows < 4 || colls < 4);
    // colls = 30;
    // rows = 30;
    std::vector<int> wallsToVisit;
    srand(time(NULL));

    maze = new bool*[rows];
    visited = new bool*[rows];
    for(int i = 0; i < rows; i++){
        maze[i] = new bool[colls];
        visited[i] = new bool[colls];
        for(int j = 0; j < colls; j++){
            maze[i][j] = false;
            visited[i][j] = false;
        }
    }
//Generate Maze
    wallsToVisit.reserve(colls > rows ? colls : rows);
    wallsToVisit.push_back(2 + colls * 1);
    wallsToVisit.push_back(1 + colls * 2);

    visited[1][1] = true;
    maze[1][1] = true;
    while(!wallsToVisit.empty()){
        int listIndex = rand() % wallsToVisit.size();
        int index = wallsToVisit[listIndex];
        if(
            MazeAt(index - 1) && !MazeAt(index + 1) && !MazeAt(index - colls) && !MazeAt(index + colls) ||
            MazeAt(index + 1) && !MazeAt(index - 1) && !MazeAt(index - colls) && !MazeAt(index + colls) ||
            MazeAt(index - colls) && !MazeAt(index + 1) && !MazeAt(index - 1) && !MazeAt(index + colls) ||
            MazeAt(index + colls) && !MazeAt(index + 1) && !MazeAt(index - colls) && !MazeAt(index - 1)
        ){
            maze[index / colls][index % colls] = true;
            //Left
            if(index % colls > 1 && !VisitedAt(index - 1)){
                visited[index / colls][index % colls - 1] = true;
                wallsToVisit.push_back(index - 1);
            }
            //Right
            if(index % colls < colls - 2 && !VisitedAt(index + 1)){
                visited[index / colls][index % colls + 1] = true;
                wallsToVisit.push_back(index + 1);
            }
            //Up
            if(index / colls > 1 && !VisitedAt(index - colls)){
                visited[index / colls - 1][index % colls] = true;
                wallsToVisit.push_back(index - colls);
            }
            //Down
            if(index / colls < rows - 2 && !VisitedAt(index + colls)){
                visited[index / colls + 1][index % colls] = true;
                wallsToVisit.push_back(index + colls);
            }
        }
        
        wallsToVisit.erase(wallsToVisit.begin() + listIndex);
    }
        
//View Maze
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colls; j++){
            if(maze[i][j])
                std::cout << ' ';
            else 
                std::cout << '#';
        }
        std::cout << std::endl;
    }
    
//destroy
    for(int i = 0; i < rows; i++){
        delete[] maze[i];
        delete[] visited[i];
    }
    delete[] visited;
    delete[] maze;
    //flush input buffer
    while(getchar() != '\n');
    getchar();
    return 0;
}

int MazeAt(const int& arg){
    return maze[arg / colls][arg % colls];
}
int VisitedAt(const int& arg){
    return visited[arg / colls][arg % colls];
}