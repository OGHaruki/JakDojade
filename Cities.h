#pragma once
#include <iostream>
#include "String.h"
#include "List.h"
#include "Vector.h"
#include "HashMap.h"
#include "PriorityQueue.h"
using namespace std;

class Cities {
private:
    int width = 0, height = 0;
    Vector<char> map;
    struct City {
        String name;
        int id;
        int coordinates_y;
        int coordinates_x;
        struct Connection {
            City* city;
            int distance;
        };
        Vector<Connection> connections;
        City() {
            this->name = "";
            this->id = 0;
            this->coordinates_y = 0;
            this->coordinates_x = 0;
        }
        explicit City(String name) {
            this->name = name;
        }
    };
    Vector<City> cities;
    HashMap citiesMap;
public:
    Cities();
    Cities(const int width, const int height);
    ~Cities();
    void ReadInput(String& source, String& destination, int &distance);   // funkcja wczytujaca dane
    void InsertMap();   // funkcja wczytujaca mape miast
    void InsertFlights(char* source, char* destination, char* distance);   // funkcja wczytujaca loty
    void InsertCities();    // funkcja wczytujaca nazwy miast
    void BFS();             // funkcja wyznaczajaca polaczenia dla kazdego miasta
    void CalculateShortestWay(String& source, const String& destination, int mode);    // funkcja wyznacza najszybszą trasę z A do B
    void PrintShortestWay();    // funkcja wypisuje najszybszą trasę z A do B
};
