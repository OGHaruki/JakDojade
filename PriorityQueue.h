#pragma once
#include <iostream>
#include "Vector.h"
using namespace std;


template <class T>
class PriorityQueue {
private:
    struct Item{
        T value;
        int priority;
    };
    Vector<Item*> data;
    int size;

public:

    PriorityQueue() {
        size = 0;
        data = Vector<Item*>();
    }

    void Push(T&& value, int priority) {
        Item *item;
        item = new Item;
        item->priority = priority;
        item->value = value;
        data.PushBack(item);
        size++;
        Heapify(size - 1);
    }

    T& Pop() {
        if(data.GetSize() != 0) {
            Item *item = data[0];
            data[0] = data[data.GetSize() - 1];
            data.DeleteLast();
            size--;
            Heapify(0);
            return item->value;
        }
        else {
            cout << "Queue is empty" << endl;
            exit(1);
        }
    }

    void Heapify(int index) {
        int temp;
        int l = 2 * index + 1;
        int r = 2 * index + 2;
        if(index == 0) {
            return;
        }
        if(l < size && data[l]->priority > data[index]->priority) {
            temp = l;
        }
        else {
            temp = index;
        }
        if(r < size && data[r]->priority > data[temp]->priority) {
            temp = r;
        }
        if(temp != index) {
            swap(data[index], data[temp]);
            Heapify(temp);
        }
    }

    void DecreasePriority(T item, int new_priority) {
        for(int i = 0; i < size; i++) {
            if(data[i]->value == item) {
                data[i]->priority = new_priority;
                Heapify(i);
                return;
            }
        }
    }

    int GetSize() {
        return size;
    }

    T& operator[](int index) const {
        return data[index]->value;
    }
};