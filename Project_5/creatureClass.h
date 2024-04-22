#ifndef CREATURE_H
#define CREATURE_H

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

using namespace std;

enum SquareType { Wall, Clear, Visited, Path };

struct coordinate {
//variables row and col
  int row, col;
};

class CreatureClass {
public:
  // default constructor
  CreatureClass();

  // default destructor
  ~CreatureClass();

//makes the creature's row up 1
  void MoveUp();
//makes the creature's row down 1
  void MoveDown();
//makes the creature's col left 1
  void MoveLeft();
//makes the creature's col right 1
  void MoveRight();

  void AssignLocation(coordinate);

  coordinate ReportLocation();

private:
  coordinate
      position; 
};

#endif
