#include "type.h"
#include <iomanip>

// Define the overloaded methods for struct type here
//compare the right hand side with the destination
//compares two flightRec objects with their destination
bool flightRec::operator <(const flightRec & rhs) const
{
  return (destination<rhs.destination);
}

//if the origin and destination of the two objects are the same, it returns true
bool flightRec::operator==(const flightRec & rhs) const
{
  return ((origin==rhs.origin) & (destination==rhs.destination));
}

//assigns one flightRec to another
flightRec& flightRec::operator=(const flightRec &rhs){
  if(this!=&rhs) {
    origin=rhs.origin;
    flightNum=rhs.flightNum;
    destination=rhs.destination;
    price=rhs.price;
  }
  return *this;

}
//overload output operator, allows for output of flightRec objects accordingly
ostream& operator<<(ostream& os, const flightRec &fl)
{
  os<<setw(15)<<fl.origin<<setw(15)<<fl.destination<<setw(10)<<fl.flightNum<<setw(4)<<"$ "<<setw(3)<<fl.price<<endl;
  return os;
}
//Implement the struct type defined in type.h here
//You may copy it from Project 3
