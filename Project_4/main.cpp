/* 
 PROGRAMMER:       Marim Abbas
 Program Description:    
  develop a program that generates flight itinerary for
  customer requests to fly from some origin city to some destination city. For each customer request, indicate
  § whether a sequence of BlueSky flights from the origin city to the destination city exists
*/ 
#include <iostream>
#include <fstream>
#include "flightMap.h"
#include <cassert>
using namespace std;
int main() {
   cout<<"debug1"<<endl;
  //open files
ifstream citiesFile;
ifstream flightsFile;  
ifstream requestsFile;

  FlightMapClass flightMap;
  //read cities and build the flight map
  citiesFile.open("cities.dat");
  flightMap.ReadCities(citiesFile);

  flightsFile.open("flights.dat");
  flightMap.BuildMap(flightsFile);

  string first_city;
  string next_city;

requestsFile.open("requests.dat");  while(requestsFile>>first_city)
    {
      requestsFile>>next_city;

      flightMap.FindPath(first_city,next_city);
    }

  citiesFile.close();
  flightsFile.close();
  requestsFile.close();


}
