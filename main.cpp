#include <iostream>
#include "Cities.h"
#include <chrono>
using namespace std;


void timeDifference(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) {
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
}

void timeDifference(std::chrono::steady_clock::time_point begin){
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    timeDifference(begin, end);
}

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    char source[100] = {}, destination[100] = {}, time[100] = {};
    int width = 0, height = 0, flightsCount = 0, testsCount = 0, size = 0;
    cin >> width >> height;
    Cities world(width, height);
    world.InsertMap();
    cout << "Map inserted" << endl;
    timeDifference(begin);
    world.InsertCities();
    cout << "Cities inserted" << endl;
    timeDifference(begin);
    world.BFS();
    cout << "BFS done" << endl;
    timeDifference(begin);
    cin >> flightsCount;
    char c = getchar();
    for(int i = 0; i < flightsCount; i++) {
        world.InsertFlights(source, destination, time);
    }
    cout << "Flights inserted" << endl;
    timeDifference(begin);
    cin >> testsCount;
    for(int i = 0; i < testsCount; i++) {
        world.PrintShortestWay();
    }
    timeDifference(begin);
    return 0;
}
