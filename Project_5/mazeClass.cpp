#include "mazeClass.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
using namespace std;

// default Constructor
MazeClass::MazeClass() {}
// Destructor to Deallocate Maze
MazeClass::~MazeClass() {
  for (int i = 0; i < height; i++) {
    delete[] Maze[i];
  }
  delete[] Maze;
}

// Reads maze from the file and Dynamycally Allocates it into the Maze
void MazeClass::ReadMaze(ifstream &myIn) {
  int R, C;
  string line;

  myIn >> R >> C;
  height = R;
  width = C;
  myIn >> R >> C;
  entrance.row = R;
  entrance.col = C;
  myIn >> R >> C;
  Exit.row = R;
  Exit.col = C;

  // dynamically allocatation
  Maze = new SquareType *[height];
  for (int i = 0; i < height; ++i)
    Maze[i] = new SquareType[width];

  myIn.ignore(100, '\n');

  // Goes through the file and assignes the maze weather it is a Wall or Clear
  for (int i = 0; i < height; i++) {
    getline(myIn, line);
    for (int j = 0; j < width; j++) {
      if (line[j] == ' ') {
        Maze[i][j] = Clear;
      } else if (line[j] == '*') {
        Maze[i][j] = Wall;
      }
    }
  }
  cout << endl;
}

// Goes through and Displays the maze appropriately
void MazeClass::DisplayMaze() {
  coordinate cord;
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
      cord.row = r;
      cord.col = c;
      if (IsClear(cord)) {
        cout << " ";
      } else if (IsPath(cord)) {
        cout << "p";
      } else if (IsVisited(cord)) {
        cout << "v";
      } else if (IsWall(cord)) {
        cout << "*";
      }
    }
    cout << endl;
  }
  cout << endl;
}
// Checks If we hit a wall
bool MazeClass::IsWall(coordinate pos) {
  return Maze[pos.row][pos.col] == Wall;
}
// Checks If we hit a clear cordinate
bool MazeClass::IsClear(coordinate pos) {
  return Maze[pos.row][pos.col] == Clear;
}
// Checks If it is path
bool MazeClass::IsPath(coordinate pos) {
  return Maze[pos.row][pos.col] == Path;
}
// Checks If we hit a visited cordinate
bool MazeClass::IsVisited(coordinate pos) {
  return Maze[pos.row][pos.col] == Visited;
}
// Checks If we hit a exit cordinate
bool MazeClass::IsExit(coordinate pos) {
  if (pos.row == Exit.row && pos.col == Exit.col) {
    return true;
  }
  return false;
}
// Checks If we are inside the grid
bool MazeClass::InMaze(coordinate pos) {
  if (pos.row > height || pos.col > width || pos.row < 0 || pos.col < 0) {
    return false;
  }
  return true;
}
// Makes it as a path coordinate P
void MazeClass::MarkPath(coordinate pos) { Maze[pos.row][pos.col] = Path; }
// makes it as a visited coordinate V
void MazeClass::MarkVisited(coordinate pos) {
  Maze[pos.row][pos.col] = Visited;
}
// returns Entrance
coordinate MazeClass::GetEntrance() { return entrance; }
