#include "flightMap.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stack>
using namespace std;

// Default Constructor
FlightMapClass::FlightMapClass() {
  size = 0;
  map = NULL;
  //visited.resize(size, false);
  //cout << "debug1" << endl;
}

// Copy Constructor
/*FlightMapClass::FlightMapClass(const FlightMapClass &f) {
  size = f.size;
  cities = f.cities;
  visited = f.visited;

  // create map to copy flight records
  map = new list<flightRec>[size];
  for (int i = 0; i < size; i++) {
    map[i] = f.map[i];
    cout << "debug2" << endl;
  }
}*/

// Destructor
FlightMapClass::~FlightMapClass() {
  if (map) {
    for (int i = 0; i < size; i++)
      map[i].clear();
    delete[] map;
  }
}

// read cities from the file
// sort them
void FlightMapClass::ReadCities(ifstream &myIn) {

  string cityNum;
  string cityNames;
  getline(myIn,cityNum);

  size=stoi(cityNum);
  cities.reserve(size);
  visited.reserve(size);

  while(getline(myIn, cityNum)) {
    cities.push_back(cityNum);
    visited.push_back(false);
  }

  sort(cities.begin(), cities.end());
}


// build flight map
void FlightMapClass::BuildMap(ifstream &myFlights) {
  map=new list<flightRec>[size];

  int flight_num, price;
  string origin, destination;

  flightRec oneFlight;

  while(myFlights>>flight_num>>origin>>destination>>price)
    {
      oneFlight.flightNum=flight_num;
      oneFlight.origin=origin;
      oneFlight.destination=destination;
      oneFlight.price=price;

      for(int i=0; i<size; i++)
        {
          if(cities[i]==oneFlight.origin)
          {
            map[i].push_back(oneFlight);
          }
          map[i].sort();
        }

      myFlights.ignore(100,'\n');



    }
  return;    
}

// display flight map
void FlightMapClass::DisplayMap() {
  cout<<left<<setw(32)<<
    "Origin"<<setw(15)<<
    "Destination"<<setw(9)<<
    "Flight"<<
    "Price"<<endl;
  cout<<"=================================================="<<endl;
  cout<<endl;

for(int i=0; i<size;i++)
  {
    list<flightRec>::iterator itr;

    cout<<" From "<<cities[i]<<setw(18-cities[i].length())<<"to: ";

    int counter=0;

    for(itr=map[i].begin();itr!=map[i].end(); itr++)
      {
        if(itr!=map[i].begin())
        {
          cout<<setw(24)<<left<<"";
          cout<<setw(15)<<itr->destination;
          cout<<setw(9)<<itr->flightNum;
          cout<<"$"<<itr->price<<endl;
        }

        else
        {
          cout<<setw(15)<<itr->destination;
          cout<<setw(9)<<itr->flightNum;
          cout<<"$"<<itr->price<<endl;

          counter++;
        }
      }

    if(counter==0)
    {
      cout<<endl;
    }
  }
}

// check whether airline serves in that city
bool FlightMapClass::CheckCity(string cityName) const {
  vector<string>::const_iterator city_itr=cities.begin();

  for(city_itr=cities.begin();city_itr !=cities.end(); city_itr++)
    {
      if(*city_itr==cityName)
      {
        return true;
      }
    }
  return false;
}

// display all of the cities
void FlightMapClass::DisplayAllCities() const {
  vector<string>::const_iterator itr;

  for(itr=cities.begin(); itr!=cities.end();itr++)
    {
      cout<<*itr<<endl;
    }

  }


// mark a cities as visited
void FlightMapClass::MarkVisited(int city)
{ 
  visited[city]=true;
}

// check if a city has been visited
bool FlightMapClass::IsVisited(int city) const
{ 
  return visited[city]; 
}

// find index correspnding to a city name in 'cities' vector
// use FindPath function to find itinerary between two cities
void FlightMapClass::FindPath(string originCity, string destinationCity) {

  cout<<"Request is to fly from "<<originCity<<" to "<<destinationCity<<endl;

  stack<int> flightstack;

  int total=0;
  int first_city, destination_index, next_city_index;
  int top_index;
  string next_city;
  string real_city=originCity;

  bool success;

  UnvisitAll();

  if(!CheckCity(originCity))
  {
    cout<<"Sorry, BlueSky airline does not fly from"<<originCity<<" to "<<destinationCity<<endl;
    return;
  }

  else if(!CheckCity(destinationCity))
  {
    cout<<"Sorry BlueSky airline does not serve "<<destinationCity<<endl;
    return;
  }

  destination_index=GetCityNumber(destinationCity);

  first_city=GetCityNumber(originCity);

  flightstack.push(first_city);

  MarkVisited(first_city);

  while(!flightstack.empty() && (flightstack.top()!=destination_index))
    {
      success=GetNextCity(GetCityName(first_city), next_city);

      if(!success)
      {
        flightstack.pop();

      }

      else
      {
        next_city_index=GetCityNumber(next_city);

        flightstack.push(next_city_index);

        MarkVisited(next_city_index);

        originCity=next_city;
      }

      if(!flightstack.empty())
      {
        first_city=flightstack.top();
      }

      if(flightstack.empty())
      {
        cout<<"Sorry, BlueSky airline does not fly from "<<real_city<<" to "<<destinationCity<<endl;
        cout<<endl;
        return;
      }



    }

  cout<<"Bluesky airline serves between these two cities: "<<endl;
  cout<<"The Flight intinary is: "<<endl;
  cout<<"Flight #          ";
  cout<<"From              ";
  cout<<"To                ";
  cout<<"Price             "<<endl;

  deque<string> copy_flightstack;

  while(!flightstack.empty())
    {
      top_index=flightstack.top();
      flightstack.pop();

      copy_flightstack.push_front(GetCityName(top_index));

    }

  for(int i=0;i<copy_flightstack.size()-1;++i)
    {
      string origin=copy_flightstack[i];

      string destination=copy_flightstack[i+1];

      list<flightRec>::iterator itr=map[GetCityNumber(origin)].begin();

      for(;itr!=map[GetCityNumber(origin)].end();++itr)
        {
          if(itr->destination==destination)
          {
            cout<<left<<setw(16)<<itr->flightNum<<setw(16)<<left<<itr->origin<<setw(17)<<itr->destination<<"$"<<itr->price<<endl;

            total+=itr->price;
          }
        }

    }

  cout<<right<<setw(50)<<"Total:      $"<<total<<endl;
  cout<<endl;


}

int FlightMapClass::GetCityNumber(string cityname) const 
{
  int i=0;

  for(;i<size;i++)
    {
      if(cities[i]==cityname)
      {
        return i;
      }

    }
  return -1;
}


// return the name of a city given its corresponding index
string FlightMapClass::GetCityName(int cityNumber) const 
{
  return cities[cityNumber];
}

// Determine the next unvisited city
bool FlightMapClass::GetNextCity(string fromCity, string &nextCity) {
  int i=GetCityNumber(fromCity);

  list<flightRec>&lists_destination=map[i];

  list<flightRec>::iterator itr=lists_destination.begin();

  for(;itr!=lists_destination.end(); itr++)
    {
      if(!visited[GetCityNumber(itr->destination)])
      {
        nextCity=itr->destination;

        return true;
      }
    }
  return false;
}

//
void FlightMapClass::UnvisitAll() {
  vector<bool>::iterator itr;

  for(itr=visited.begin();itr!=visited.end(); itr++)
    {
      *itr=false;
    }
}
