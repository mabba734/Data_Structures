
#include "creatureClass.h"
#include "mazeClass.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
using namespace std;

// function prototypes

// Goes towards the North side of the Maze of a Creature
void GoNorth(MazeClass &maze, CreatureClass &creature, bool &success);
// Goes towards the South side of the Maze of a Creature
void GoSouth(MazeClass &maze, CreatureClass &creature, bool &success);
// Goes towards the East side of the Maze of a Creature
void GoEast(MazeClass &maze, CreatureClass &creature, bool &success);
// Goes towards the North side of the Maze of a Creature
void GoWest(MazeClass &maze, CreatureClass &creature, bool &success);

int main() {
  string file;
  cout << "Please enter the name of the Maze File to read:  ";
  cin >> file;
  cout << endl << endl;
  // open the file into myIn
  ifstream myIn(file);
  assert(myIn);
  MazeClass maze;
  CreatureClass creature;
  maze.ReadMaze(myIn); // Read the file into Maze

  cout << "Maze Bafore" << endl;
  maze.DisplayMaze();

  bool success = false; // to check if we need to go another direction
  coordinate temp;      // entrance

  temp.row = maze.GetEntrance().row;
  temp.col = maze.GetEntrance().col;
  creature.AssignLocation(temp);

  // if sucess is false, go another direction
  GoNorth(maze, creature, success);
  if (!success) {
    GoEast(maze, creature, success);
  }
  if (!success) {
    GoWest(maze, creature, success);
  }
  if (!success) {
    GoSouth(maze, creature, success);
  }
  // if sucess is true, we found a math and mark it as path P
  if (success) {
    maze.MarkPath(temp);
  }
  // otherwise make it visited V
  else {
    maze.MarkVisited(temp);
  }
  cout << endl;

  cout << "Maze After" << endl;
  maze.DisplayMaze();
}

// This fucntions if Success if false, goes north until it finds a exit or else
// goes every direction as log as sucess is flase when returned and returns true
// Exit is found elase returns false
void GoNorth(MazeClass &maze, CreatureClass &Creature, bool &success) {
  coordinate tmpPos;
  CreatureClass creature; // temp creature
  tmpPos = Creature.ReportLocation();
  creature.AssignLocation(tmpPos);
  tmpPos.row++;

  if (maze.InMaze(tmpPos) && maze.IsClear(tmpPos) && !maze.IsVisited(tmpPos)) {
    creature.MoveUp();
    tmpPos = creature.ReportLocation();
    maze.MarkPath(tmpPos);
    if (maze.IsExit(tmpPos)) {
      success = true;
    } else {
      GoNorth(maze, creature, success);
      if (!success) {
        GoWest(maze, creature, success);
        if (!success) {
          GoEast(maze, creature, success);
          if (!success) {
            maze.MarkVisited(tmpPos);
            GoSouth(maze, creature, success);
          }
        }
      }
    }
  } else {
    success = false;
  }
}

// This fucntions if Success if false, goes west until it finds a exit or else
// goes every direction as log as sucess is flase when returned and returns true
// Exit is found elase returns false
void GoWest(MazeClass &maze, CreatureClass &Creature, bool &success) {

  coordinate tmpPos;
  CreatureClass creature; // temp creature
  tmpPos = Creature.ReportLocation();
  creature.AssignLocation(tmpPos);
  tmpPos.col--;
  if (maze.InMaze(tmpPos) && maze.IsClear(tmpPos) && !maze.IsVisited(tmpPos)) {
    creature.MoveLeft();
    tmpPos = creature.ReportLocation();
    maze.MarkPath(tmpPos);
    if (maze.IsExit(tmpPos)) {
      success = true;
    } else {
      GoWest(maze, creature, success);
      if (!success) {
        GoNorth(maze, creature, success);
        if (!success) {
          GoSouth(maze, creature, success);
          if (!success) {
            maze.MarkVisited(tmpPos);
            GoEast(maze, creature, success);
          }
        }
      }
    }
  } else {
    success = false;
  }
}
// This fucntions if Success if false, goes east until it finds a exit or else
// goes every direction as log as sucess is flase when returned and returns true
// Exit is found elase returns false
void GoEast(MazeClass &maze, CreatureClass &Creature, bool &success) {

  coordinate tmpPos;
  CreatureClass creature; // temp creature
  tmpPos = Creature.ReportLocation();
  creature.AssignLocation(tmpPos);
  tmpPos.col++;
  if (maze.InMaze(tmpPos) && maze.IsClear(tmpPos) && !maze.IsVisited(tmpPos)) {
    creature.MoveRight();
    tmpPos = creature.ReportLocation();
    maze.MarkPath(tmpPos);
    if (maze.IsExit(tmpPos)) {
      success = true;
    } else {
      GoEast(maze, creature, success);
      if (!success) {

        GoNorth(maze, creature, success);
        if (!success) {

          GoSouth(maze, creature, success);
          if (!success) {
            maze.MarkVisited(tmpPos);
            GoWest(maze, creature, success);
          }
        }
      }
    }
  } else {
    success = false;
  }
}
// This fucntions if Success if false, goes south until it finds a exit or else
// goes every direction as log as sucess is flase when returned and returns true
// Exit is found elase returns false
void GoSouth(MazeClass &maze, CreatureClass &Creature, bool &success) {

  coordinate tmpPos;
  CreatureClass creature; // temp creature
  tmpPos = Creature.ReportLocation();
  creature.AssignLocation(tmpPos);
  tmpPos.row--;
  if (maze.InMaze(tmpPos) && maze.IsClear(tmpPos) && !maze.IsVisited(tmpPos)) {
    creature.MoveDown();
    tmpPos = creature.ReportLocation();
    maze.MarkPath(tmpPos);
    if (maze.IsExit(tmpPos)) {
      success = true;
    } else {
      GoSouth(maze, creature, success);
      if (!success) {
        GoWest(maze, creature, success);
        if (!success) {
          GoEast(maze, creature, success);
          if (!success) {
            maze.MarkVisited(tmpPos);
            GoNorth(maze, creature, success);
          }
        }
      }
    }
  } else {
    success = false;
  }
}
