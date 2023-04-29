#pragma once
#include <iostream>
using namespace std;

template <class T>
class Vector {
    T* data;
    int size{};
    int current{};

public:

    Vector() {
        current = 0;
        size = 0;
        data = nullptr;
    }

    Vector(const Vector &other) {
        data = nullptr;
        size = 0;
        for(int i = 0; i < other.size; i++) {
            PushBack(other[i]);
        }
    }

    explicit Vector(int size) {
        current = 0;
        this->size = size;
        data = new T[size];
    }

    Vector(int size, T value) {
        current = 0;
        this->size = size;
        data = new T[size];
        for(int i = 0; i < size; i++) {
            data[i] = value;
        }
    }

    ~Vector() {
        delete[] data;
        size = 0;
        current = 0;
    }

    void PushBack(T new_data) {
        if(current == size) {
            T* pom = new T[2 * size + 1];
            for(int i = 0; i < size; i++) {
                pom[i] = data[i];
            }
            delete[] data;
            size = size * 2 + 1;
            data = pom;
        }
        data[current] = new_data;
        current++;
    }

    void Delete(int index) {
        if(index == current) {
            current--;
        }
        else {
            for(int i = index; i < current; i++) {
                data[i] = data[i + 1];
            }
            current--;
        }
    }

    void DeleteLast() {
        current--;
    }

    T getElement(int index) {
        if(index < current) {
            return data[index];
        }
    }

    void Clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        current = 0;
    }

    int GetIndex() {
        return current;
    }

    int GetSize() {
        return current;
    }

    void Print()
    {
        for (int i = 0; i < current; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    T& operator[](int index) const {
        return data[index];
    }

    Vector<T>& operator=(const Vector &right) {
        if(this == &right) {
            return *this;
        }
        Vector pom = right;
        std::swap(data, pom.data);
        size = pom.size;
        current = pom.current;
        return *this;
    }

    void Resize(int newSize) {
        T* temp = new T[newSize];
        int elements_to_copy;
        if(data != nullptr) {
            if(newSize < current) {
                elements_to_copy = current;
            }
            else {
                elements_to_copy = newSize;
            }
            for(int i = 0; i < elements_to_copy; i++) {
                if(data[i] != nullptr) {
                    temp[i] = data[i];
                }
            }
        }
        delete[] data;
        data = temp;
        size = newSize;
        current = elements_to_copy;
    }
};
