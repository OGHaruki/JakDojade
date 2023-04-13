#include "Cities.h"
#include <iostream>
using namespace std;

#define INF INT32_MAX

Cities::Cities() {
    this->width = 0;
    this->height = 0;
}

Cities::Cities(const int width, const int height) {
    this->width = width;
    this->height = height;
}

void Cities::BFS() {
    int pom = 0;
    bool found = false;
    bool *visited = new bool[height * width];
    int *distance = new int[height * width];
    for (int i = 0; i < height * width; i++) {
        visited[i] = false;
        distance[i] = 0;
    }
    for (int k = 0; k < cities.GetSize(); k++) {
        DoubleLinkedList<std::pair<int, int>> queue;             // wykorzystuje wczesniej stworzona liste jako kolejke
        queue.PushBack(std::make_pair(cities[k].coordinates_x, cities[k].coordinates_y));
        while (queue.GetSize() != 0) {
            std::pair<int, int> temp = queue[0];
            queue.RemoveByIndex(0);
            visited[temp.first * width + temp.second] = true;
            if (map[temp.first][temp.second] == '*' && pom != 0) {
                found = true;
                City::Connection c;
                c.distance = distance[temp.first * width + temp.second];
                for(int z = 0; z < cities.GetSize(); z++) {
                    if (cities[z].coordinates_x == temp.first && cities[z].coordinates_y == temp.second) {
                        c.city = &(cities[z]);
                        cities[k].connections.PushBack(c);
                        break;
                    }
                }
            }
            if(!found) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if ((i == -1 && j == 0) || (i == 0 && j == -1) || (i == 0 && j == 1) || (i == 1 && j == 0)) {
                            if(temp.first + i >= 0 && temp.first + i < height && temp.second + j >= 0 && temp.second + j < width) {
                                if(!visited[(temp.first + i) * width + (temp.second + j)]){
                                    if(map[temp.first + i][temp.second + j] == '#' || map[temp.first + i][temp.second + j] == '*') {
                                        queue.PushBack(std::make_pair(temp.first + i, temp.second + j));
                                        visited[(temp.first + i) * width + (temp.second + j)] = true;
                                        distance[(temp.first + i) * width + (temp.second + j)] = distance[temp.first * width + temp.second] + 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            pom++;
            found = false;
        }
        pom = 0;
        for (int i = 0; i < height * width; i++) {
            visited[i] = false;
            distance[i] = 0;
        }
    }
    delete[] visited;
    delete[] distance;
}

void Cities::InsertMap() {
    char c;
    for(int i = 0; i < height; i++) {
        Vector<char> temp;
        for(int j = 0; j < width; j++) {
            cin >> c;
            temp.PushBack(c);
        }
        map.PushBack(temp);
    }
}

void Cities::InsertCities() {
    int index = 0;
    int temp = 0;
    String temp_name;
    bool flag = false;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(map[i][j] == '*') {
                for(int k = -1; k <= 1; k++) {
                    for(int n = -1; n <= 1; n++) {
                        if(k == 0 && n == 0) continue;
                        else {
                            if(i + k >= 0 && i + k < height && j + n >= 0 && j + n < width) {
                                if (char(map[i + k][j + n]) >= 'A' && char(map[i + k][j + n]) <= 'Z'
                                    || (char(map[i + k][j + n]) >= '0' && char(map[i + k][j + n]) <= '9')) {
                                    temp = n;
                                    while(map[i + k][j + temp - 1] != '.' && map[i + k][j + temp - 1] != '#' && map[i + k][j + temp - 1] != '*' && j + temp - 1 >= 0) {
                                        temp--;
                                    }
                                    while(map[i + k][j + temp] != '.' && map[i + k][j + temp] != '#' && map[i + k][j + temp] != '*' && j + temp < width) {
                                        temp_name.PushBack(map[i + k][j + temp]);
                                        temp++;
                                    }
                                    flag = true;
                                    City c(temp_name);
                                    c.id = index;
                                    c.coordinates_x = i;
                                    c.coordinates_y = j;
                                    cities.PushBack(c);
                                    break;
                                }
                            }
                        }
                    }
                    if(flag) break;
                }
                temp_name.Clear();
                flag = false;
                temp = 0;
                index++;
            }
        }
    }
}

void Cities::CalculateShortestWay(String& source, const String& destination, int mode) {
    int final_index = 0;
    int start_index = 0;
    int *distance = new int[cities.GetSize()];
    City** previous = new City*[cities.GetSize()];
    DoubleLinkedList<City*> queue;
    for(int i = 0; i < cities.GetSize(); i++) {
        if(cities[i].name == destination) {
            final_index = i;
        }
        if(cities[i].name == source) {
            start_index = i;
        }
        distance[i] = INF;
        previous[i] = nullptr;
        queue.PushBack(&(cities[i]));
    }
    if(start_index == final_index) {
        cout << "0" << endl;
        return;
    }
    distance[start_index] = 0;
    int temp_distance;
    int remove_index;
    City* current;
    while(queue.GetSize() != 0) {
        int total_distance = 0;
        temp_distance = INF;
        for(int j = 0; j < queue.GetSize(); j++) {
            if(distance[queue[j]->id] <= temp_distance) {
                temp_distance = distance[queue[j]->id];
                current = queue[j];
                remove_index = j;
            }
        }
        queue.RemoveByIndex(remove_index);          // usuwamy z kolejki miasto o najmniejszej odl
        if (current->id == final_index) {
            break;
        }
        for(int j = 0; j < current->connections.GetSize(); j++) {
            for(int k = 0; k < queue.GetSize(); k++) {
                int queueID = queue[k]->id;
                int id = current->connections[j].city->id;
                if (queueID == id) {
                    total_distance = distance[current->id] + cities[current->id].connections[j].distance;
                    if (total_distance < distance[current->connections[j].city->id]) {
                        distance[current->connections[j].city->id] = total_distance;
                        previous[current->connections[j].city->id] = &cities[current->id];
                    }
                }
            }
        }
    }
    if(mode == 0) {
        cout << distance[final_index];
    }
    else if(mode == 1) {
        cout << distance[final_index] << " ";
        Vector<String> ShortestPath;
        City *temp;
        // koncowe miasto znajduje sie pod indeksem final_index
        temp = previous[final_index];
        if(previous[final_index] != nullptr) {
            while(temp != nullptr && !(temp->name == source)) {
                ShortestPath.PushBack(temp->name);
                for (int i = 0; i < cities.GetSize(); i++) {
                    if (cities[i].name == temp->name) {
                        final_index = i;
                        break;
                    }
                }
                temp = previous[final_index];
            }
        }
        for(int i = ShortestPath.GetSize() - 1; i >= 0; i--) {
            cout << ShortestPath[i] << " ";
        }
    }
    delete[] previous;
    delete[] distance;
}

void Cities::PrintMap() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

Cities::~Cities() {
    this->width = 0;
    this->height = 0;
    map.Clear();
    cities.Clear();
}

void Cities::PrintCities() {
    for(int i = 0; i < cities.GetIndex(); i++) {
        cout << "City: " << cities[i].name << endl;
        for(int j = 0; j < cities[i].connections.GetIndex(); j++) {
            cout << cities[i].connections[j].city->name << " - " << cities[i].connections[j].distance << endl;
        }
    }
}

int StringToInt(String& time) {
    int distance = 0;
    for(int i = 0; i < time.GetLength(); i++) {
         distance = distance * 10 + (time[i] - '0');
    }
    return distance;
}

void Cities::ReadInput(String& source, String& destination, int &distance) {
    char c;
    String time;
    c = getchar();
    if(c == '\n') {
        c = getchar();
    }
    while(c != ' ') {
        source.PushBack(c);
        c = getchar();
    }
    c = getchar();
    while(c != ' ') {
        destination.PushBack(c);
        c = getchar();
    }
    c = getchar();
    while(c != '\n') {
        time.PushBack(c);
        c = getchar();
    }
    distance = StringToInt(time);
}

void Cities::InsertFlights() {
    String source, destination;
    int distance = 0;
    ReadInput(source, destination, distance);
    City::Connection new_connection;
    new_connection.distance = distance;
    for(int i = 0; i < cities.GetSize(); i++) {
        if(cities[i].name == destination) {
            new_connection.city = &cities[i];
            break;
        }
    }
    for(int i = 0; i < cities.GetSize(); i++) {
        if(cities[i].name == source) {
            cities[i].connections.PushBack(new_connection);
            break;
        }
    }
    source.Clear();
    destination.Clear();
}

void Cities::PrintShortestWay() {
    String source, destination;
    int mode = 0;
    ReadInput(source, destination, mode);
    CalculateShortestWay(source, destination, mode);
    cout << endl;
}

