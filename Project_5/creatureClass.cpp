#include "creatureClass.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
using namespace std;

CreatureClass::CreatureClass() {
  position.row = 0; // set creature row  to zero
  position.col = 0; // set creature col to zero
}
CreatureClass::~CreatureClass() {}

//makes the creature's row up 1
void CreatureClass::MoveUp() {
  position.row++; 
}
//makes the creature's row down 1
void CreatureClass::MoveDown() {
  position.row--;
}
//makes the creature's col left 1
void CreatureClass::MoveLeft() {
  position.col--; 
}
//makes the creature's col right 1
void CreatureClass::MoveRight() {
  position.col++; 
}
//changes position to the given position
void CreatureClass::AssignLocation(coordinate pos) {
  position.row = pos.row;
  position.col = pos.col;
}
//returns current position
coordinate CreatureClass::ReportLocation() {
  return position;
}
