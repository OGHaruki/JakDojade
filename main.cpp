#include <iostream>
#include "Cities.h"
using namespace std;

int main() {
    int width = 0, height = 0, flightsCount = 0, testsCount = 0;
    cin >> width >> height;
    Cities world(width, height);
    world.InsertMap();
    world.InsertCities();
    world.BFS();
    cin >> flightsCount;
    for(int i = 0; i < flightsCount; i++) {
        world.InsertFlights();
    }
    cin >> testsCount;
    for(int i = 0; i < testsCount; i++) {
        world.PrintShortestWay();
    }
    return 0;
}
