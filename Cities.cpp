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
    City **coordinates = new City*[height * width];
    int temp = 0;
    for (int i = 0; i < height * width; i++) {
        visited[i] = false;
        distance[i] = 0;
        if(map[i] == '*') {
            coordinates[i] = &cities[temp];
            temp++;
        }
        else
            coordinates[i] = nullptr;
    }
    for (int k = 0; k < cities.GetSize(); k++) {
        int num_of_roads = 0;
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                if((i == -1 && j == 0) || (i == 0 && j == -1) || (i == 0 && j == 1) || (i == 1 && j == 0)) {
                    if(cities[k].coordinates_y + i >= 0 && cities[k].coordinates_y + i < height && cities[k].coordinates_x + j >= 0 && cities[k].coordinates_x + j < width) {
                        if(map[(cities[k].coordinates_y + i) * width + cities[k].coordinates_x + j] == '#' ||
                            map[(cities[k].coordinates_y + i) * width + cities[k].coordinates_x + j] == '*')
                            num_of_roads++;
                    }
                }
            }
        }
        if(num_of_roads == 0) {
            continue;
        }
        DoubleLinkedList<std::pair<int, int>> queue;      // wykorzystuje wczesniej stworzona liste jako kolejke
        queue.PushBack(std::make_pair(cities[k].coordinates_y, cities[k].coordinates_x));
        while (queue.GetSize() != 0) {
            std::pair<int, int> temp = queue[0];
            queue.RemoveByIndex(0);
            visited[temp.first * width + temp.second] = true;
            if (map[temp.first * width + temp.second] == '*' && pom != 0) {
                found = true;
                City::Connection c;
                c.distance = distance[temp.first * width + temp.second];
                c.city = coordinates[temp.first * width + temp.second];
                cities[k].connections.PushBack(c);
            }
            if(!found) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if ((i == -1 && j == 0) || (i == 0 && j == -1) || (i == 0 && j == 1) || (i == 1 && j == 0)) {
                            if(temp.first + i >= 0 && temp.first + i < height && temp.second + j >= 0 && temp.second + j < width) {
                                if(!visited[(temp.first + i) * width + (temp.second + j)]){
                                    if(map[(temp.first + i) * width + temp.second + j] == '#' || map[(temp.first + i) * width + temp.second + j] == '*') {
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
    delete[] coordinates;
}

void Cities::InsertMap() {
    char c;
    for(int i = 0; i < height * width; i++) {
        cin >> c;
        map.PushBack(c);
    }
}

void Cities::InsertCities() {
    int index = 0;
    int temp = 0;
    String temp_name;
    bool flag = false;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(map[i * width + j] == '*') {
                for(int k = -1; k <= 1; k++) {
                    for(int n = -1; n <= 1; n++) {
                        if(k == 0 && n == 0) continue;
                        else {
                            if(i + k >= 0 && i + k < height && j + n >= 0 && j + n < width) {
                                if (char(map[(i + k) * width + j + n]) >= 'A' && char(map[(i + k) * width + j + n]) <= 'Z'
                                    || (char(map[(i + k) * width + j + n]) >= '0' && char(map[(i + k) * width + j + n]) <= '9')) {
                                    temp = n;
                                    while(map[(i + k) * width + j + temp - 1] != '.' && map[(i + k) * width + j + temp - 1] != '#' && map[(i + k) * width + j + temp - 1] != '*' && j + temp - 1 >= 0) {
                                        temp--;
                                    }
                                    while(map[(i + k) * width + j + temp] != '.' && map[(i + k) * width + j + temp] != '#' && map[(i + k) * width + j + temp] != '*' && j + temp < width) {
                                        temp_name.PushBack(map[(i + k) * width + j + temp]);
                                        temp++;
                                    }
                                    flag = true;
                                    City c(temp_name);
                                    c.id = index;
                                    c.coordinates_y = i;
                                    c.coordinates_x = j;
                                    cities.PushBack(c);
                                    citiesMap.SetItem(temp_name, index);
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
    int final_index = citiesMap.GetItem(destination);
    int start_index = citiesMap.GetItem(source);
    if(start_index == final_index) {
        cout << "0" << endl;
        return;
    }
    bool *isInQueue = new bool[height * width];
    int *distance = new int[cities.GetSize()];
    City** previous = new City*[cities.GetSize()];
    distance[start_index] = 0;
    previous[start_index] = nullptr;
    PriorityQueue<City*> queue;
    for(int i = 0; i < cities.GetSize(); i++) {
        if(i != start_index) {
            distance[i] = INT_MAX;
            previous[i] = nullptr;
            isInQueue[i] = false;
        }
    }
    queue.Push(&(cities[start_index]), distance[start_index]);
    isInQueue[start_index] = true;
    City* current;
    while(queue.GetSize() != 0) {
        int total_distance = 0;
        current = queue.Pop();
        isInQueue[current->id] = false;
        for(int j = 0; j < current->connections.GetSize(); j++) {
            total_distance = distance[current->id] + cities[current->id].connections[j].distance;
            if (total_distance < distance[current->connections[j].city->id]) {
                distance[current->connections[j].city->id] = total_distance;
                previous[current->connections[j].city->id] = &cities[current->id];
                if (!isInQueue[current->connections[j].city->id]) {
                    queue.Push(&cities[current->connections[j].city->id], total_distance);
                    isInQueue[current->connections[j].city->id] = true;
                }
            }
        }
        //if(current->id == final_index) break;
    }
    if(mode == 0) {
        cout << distance[final_index];
    }
    else if(mode == 1) {
        cout << distance[final_index] << " ";
        Vector<String> ShortestPath;
        City *temp;
        temp = previous[final_index];
        if(previous[final_index] != nullptr) {
            while(temp != nullptr && !(temp->name == source)) {
                ShortestPath.PushBack(temp->name);
                final_index = citiesMap.GetItem(temp->name);
                temp = previous[final_index];
            }
        }
        for(int i = ShortestPath.GetSize() - 1; i >= 0; i--) {
            cout << ShortestPath[i] << " ";
        }
    }
    delete[] isInQueue;
    delete[] previous;
    delete[] distance;
}

Cities::~Cities() {
    this->width = 0;
    this->height = 0;
    map.Clear();
    cities.Clear();
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

void Cities::InsertFlights(char* source, char* destination, char* distance) {
    char c;
    int size = 0;
    do {
        c = fgetc(stdin);
        source[size] = c;
        size++;
    } while(c != ' ');
    source[size - 1] = '\0';
    size = 0;
    do {
        c = fgetc(stdin);
        destination[size] = c;
        size++;
    } while(c != ' ');
    destination[size - 1] = '\0';
    size = 0;
    do {
        c = fgetc(stdin);
        distance[size] = c;
        size++;
    } while(c != '\n');
    distance[size - 1] = '\0';
    City::Connection new_connection;
    new_connection.distance = atoi(distance);
    int index = citiesMap.GetItem(destination);
    if(index != -1) {
        new_connection.city = &cities[index];
    }
    index = citiesMap.GetItem(source);
    if(index != -1) {
        cities[index].connections.PushBack(new_connection);
    }
}

void Cities::PrintShortestWay() {
    String source, destination;
    int mode = 0;
    ReadInput(source, destination, mode);
    CalculateShortestWay(source, destination, mode);
    cout << endl;
}

