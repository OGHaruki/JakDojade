#pragma once
#include <cmath>
#include <iostream>
#include "Vector.h"
using namespace std;
class Cities;
#define CAPACITY 100003

class HashMap {
private:
    struct Item {
        String key;
        int value;
        struct Item* next;
    };
    Vector<Item*> data;
    unsigned int size;

public:
    HashMap() {
        size = 0;
        data = Vector<Item*>(CAPACITY);
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = nullptr;
        }
    }

    static unsigned int hashFunction(String key) {
        unsigned int hash = 998443;
        int c;
        for(int i = 0; i < key.GetLength(); i++) {
            c = key[i];
            hash = ((hash << 5) + hash) + c;
        }
        return hash % CAPACITY;
    }

    static unsigned int hashFunctionChar(char* key) {
        unsigned int hash = 998443;
        int c;
        while(*key != '\0') {
            c = *key;
            hash = ((hash << 5) + hash) + c;
            key++;
        }
        return hash % CAPACITY;
    }


    int GetItem(String key) {
        unsigned int index = hashFunction(key);
        Item* current = data[index];
        for(current; current != nullptr; current = current->next) {
            if(current->key == key) {
                return current->value;
            }
        }
        return -1;
    }

    int GetItem(char* key) {
        unsigned int index = hashFunctionChar(key);
        Item* current = data[index];
        for(current; current != nullptr; current = current->next) {
            if(current->key == key) {
                return current->value;
            }
        }
        return -1;
    }

    void SetItem(String key, int value) {
        unsigned int index = hashFunction(key);
        Item* current = data[index];
        for(current; current != nullptr; current = current->next) {
            if(current->key == key) {
                current->value = value;
                return;
            }
        }
        Item* newItem = new Item;
        newItem->key = key;
        newItem->value = value;
        newItem->next = data[index];
        data[index] = newItem;
        size++;
    }
};