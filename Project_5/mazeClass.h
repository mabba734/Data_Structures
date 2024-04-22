#ifndef MAZE_H
#define MAZE_H

#include "creatureClass.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class MazeClass {
public:
  // default Constructor
  MazeClass();
  // default Destructor to Deallocate Maze
  ~MazeClass();
  // Reads maze from the file and Dynamycally Allocates it into the Maze
  void ReadMaze(ifstream &);
  // Goes through and Displays the maze appropriately
  void DisplayMaze();
  // Checks If we hit a wall
  bool IsWall(coordinate);
  // Checks If we hit a clear cordinate
  bool IsClear(coordinate);
  // Checks If it is path
  bool IsPath(coordinate);
  // Checks If we hit a visited cordinate
  bool IsVisited(coordinate);
  // Checks If we hit a exit cordinate
  bool IsExit(coordinate);
  // Checks If we are inside the grid
  bool InMaze(coordinate);
  // Makes it as a path coordinate P
  void MarkPath(coordinate);
  // makes it as a visited coordinate V
  void MarkVisited(coordinate);

  // returns Entrance
  coordinate GetEntrance();

private:
  SquareType **Maze; // stores the maze (2d array)
  coordinate entrance,
      Exit; // stores the entrace of the maze and exit of the maze coordinate
  int height,
      width; // stores the max height of the maze and max width of the maze
};

#endif
