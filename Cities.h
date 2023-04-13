#pragma once
#include <iostream>
#include "String.h"
#include "List.h"
#include "Vector.h"
using namespace std;

class Cities {
private:
    int width = 0, height = 0;
    Vector<Vector<char>> map;
    struct City {
        String name;
        int id;
        int coordinates_x;
        int coordinates_y;
        struct Connection {
            City* city;
            int distance;
        };
        Vector<Connection> connections;
        City() {
            this->name = "";
            this->id = 0;
            this->coordinates_x = 0;
            this->coordinates_y = 0;
        }
        explicit City(String name) {
            this->name = name;
        }
    };
    Vector<City> cities;
public:
    Cities();
    Cities(const int width, const int height);
    ~Cities();
    void ReadInput(String& source, String& destination, int &distance);   // funkcja wczytujaca dane
    void InsertMap();   // funkcja wczytujaca mape miast
    void InsertFlights();   // funkcja wczytujaca loty
    void PrintMap();    // funkcja wypisujaca mape miast
    void PrintCities(); // funkcja wypisujaca miasta
    void InsertCities();    // funkcja wczytujaca nazwy miast
    void BFS();             // funkcja wyznaczajaca polaczenia dla kazdego miasta
    void CalculateShortestWay(String& source, const String& destination, int mode);    // funkcja wyznacza najszybszą trasę z A do B
    void PrintShortestWay();    // funkcja wypisuje najszybszą trasę z A do B
};