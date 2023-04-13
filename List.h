// Created by adamj on 18.03.2023.
#pragma once
#include <iostream>

#define LAST_CELL 7
#define TAB_SIZE 8

template <class T>
class DoubleLinkedList {
private:
    int counter;
    int elements_in_list{};
public:
    typedef struct ListElement {
        T data;
        T tab[8];
        bool is_taken[8];   // tworze tablice ktora przechowywuje info o tym czy komorka jest juz zajeta
        int num_elements;   // zmienna ktora przechowuje liczbe elementow w tab
        ListElement * next;
        ListElement * previous;
        ListElement() {
            num_elements = 0;
            next = nullptr;
            previous = nullptr;
            for(int i = 0; i < LAST_CELL + 1; i++) {
                is_taken[i] = false;
            }
        }
    }ListElement_type;
    ListElement_type *head;
    ListElement_type *tail;

    DoubleLinkedList() {
        counter = 0;
        elements_in_list = 0;
        head = nullptr;
        tail = nullptr;
    };

    DoubleLinkedList(const DoubleLinkedList& other) {
        head = nullptr;
        tail = nullptr;
        counter = 0;
        for(int i = 0; i < other.counter; i++) {
            PushBack(other[i]);
        }
    }

    DoubleLinkedList(DoubleLinkedList&& other) {
        counter = other.elements_in_list;
        other.counter = 0;
        elements_in_list = other.elements_in_list;
        other.elements_in_list = 0;
        tail = other.tail;
        other.tail = nullptr;
        head = other.head;
        other.head = nullptr;
    }

    ~DoubleLinkedList(){
        Clear();
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& otherList) {
        DoubleLinkedList pom = otherList;
        std::swap(head, pom.head);
        std::swap(tail, pom.tail);
        counter = pom.counter;
        return *this;
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& otherList) {
        std::swap(head, otherList.head);
        std::swap(tail, otherList.tail);
        counter = otherList.counter;
        elements_in_list = otherList.elements_in_list;
        return *this;
    }

    void PushBack(const T& data) {
        if(head == nullptr) {
            ListElement_type  *newNode = new ListElement_type();
            newNode->tab[0] = data;
            newNode->is_taken[0] = true;
            newNode->next = head;
            newNode->previous = nullptr;
            head = newNode;
            if(counter == 0) {
                tail = head;
            }
        }
        else {
            if(tail->is_taken[LAST_CELL] == true) {
                ListElement_type  *newNode = new ListElement_type();
                newNode->tab[0] = data;
                newNode->is_taken[0] = true;
                newNode->next = nullptr;
                newNode->previous = tail;
                tail->next = newNode;
                tail = newNode;
            }
            else {
                for(int i = LAST_CELL; i >= 0; i--) {
                    if(tail->is_taken[i] == false && tail->is_taken[i-1] == true) {
                        tail->tab[i] = data;
                        tail->is_taken[i] = true;
                    }
                }
            }
        }
        tail->num_elements += 1;
        counter++;
        elements_in_list++;
        return;
    }

    void PushBack(T&& data) {
        if(head == nullptr) {
            ListElement_type  *newNode = new ListElement_type();
            newNode->tab[0] = std::move(data);
            newNode->is_taken[0] = true;
            newNode->next = head;
            newNode->previous = nullptr;
            head = newNode;
            if(counter == 0) {
                tail = head;
            }
        }
        else {
            if(tail->is_taken[LAST_CELL] == true) {
                ListElement_type  *newNode = new ListElement_type();
                newNode->tab[0] = std::move(data);
                newNode->is_taken[0] = true;
                newNode->next = nullptr;
                newNode->previous = tail;
                tail->next = newNode;
                tail = newNode;
            }
            else {
                for(int i = LAST_CELL; i >= 0; i--) {
                    if(tail->is_taken[i] == false && tail->is_taken[i-1] == true) {
                        tail->tab[i] = std::move(data);
                        tail->is_taken[i] = true;
                    }
                }
            }
        }
        tail->num_elements += 1;
        counter++;
        return;
    }

    void RemoveByIndex(int index) {
        if(counter == 0 || index < 0) {
            return;
        }
        else {
            int pom2 = 0;
            int tab_index = 0;
            ListElement_type * current_node = head;
            while(pom2 + current_node->num_elements <= index) {
                pom2 += current_node->num_elements;
                current_node = current_node->next;
            }
            int tmp = 0;
            for(int i = 0; i < TAB_SIZE; i++) {
                if(pom2 + tmp == index && current_node->is_taken[i] == true) {
                    tab_index = i;
                    break;
                }
                if(current_node->is_taken[i] == true)
                    pom2++;
            }
            current_node->is_taken[tab_index] = false;
            int pom = 0;
            for(int i = 0; i < TAB_SIZE; i++) {
                if(current_node->is_taken[i] == false) pom++;
            }
            if(pom == 8) {
                if(current_node == head && current_node == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                else if(current_node == head) {
                    head->next->previous = nullptr;
                    head = head->next;

                }
                else if(current_node == tail) {
                    tail->previous->next = nullptr;
                    tail = tail->previous;
                }
                else {
                    current_node->next->previous = current_node->previous;
                    current_node->previous->next = current_node->next;
                }
            }
            counter--;
            current_node->num_elements -= 1;
        }
    }

    void RemoveByElement(T&& elementToDelete) {
        if(head == nullptr) {
            return;
        }
        else {
            int tab_index;
            int tmp;
            ListElement_type * current_node = head;
            tmp = TAB_SIZE;
            for(int i = 0; i < elements_in_list; i++) {
                if(i == tmp) {
                    current_node = current_node->next;
                    tmp += TAB_SIZE;
                }
                tab_index = i % TAB_SIZE;
                if(current_node->tab[tab_index] == elementToDelete) {
                    current_node->is_taken[tab_index] = false;
                    current_node->num_elements -= 1;
                }
            }
            int pom = 0;
            for(int i = 0; i < TAB_SIZE; i++) {
                if(current_node->is_taken[i] == false) pom++;
            }
            if(pom == 8) {
                if(current_node == head && current_node == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                else if(current_node == head) {
                    head->next->previous = nullptr;
                    head = head->next;

                }
                else if(current_node == tail) {
                    tail->previous->next = nullptr;
                    tail = tail->previous;
                }
                else {
                    current_node->next->previous = current_node->previous;
                    current_node->previous->next = current_node->next;
                }
            }
            counter--;
            current_node->num_elements -= 1;
        }
    }

    void Clear() {
        ListElement_type *tmp;
        while(head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        elements_in_list = 0;
        counter = 0;
    }

    ListElement_type * GetNode(int index) {
        int pom = 0;
        ListElement_type * current_node = head;
        while(pom + current_node->num_elements <= index) {
            pom += current_node->num_elements;
            current_node = current_node->next;
        }
        return current_node;
    }

    T& GetElement(int index) const{
        int pom = 0;
        int tab_index = 0;
        ListElement_type * current_node = head;
        while(current_node != nullptr && pom + current_node->num_elements <= index) {
            pom += current_node->num_elements;
            current_node = current_node->next;
        }
        int pom2 = 0;
        for(int i = 0; i < TAB_SIZE; i++) {
            if(pom + pom2 >= index && current_node->is_taken[i] == true) {
                tab_index = i;
                break;
            }
            if(current_node->is_taken[i] == true)
                pom2++;
        }
        return current_node->tab[tab_index];
    }

    int GetSize() {
        return counter;
    }

    const T& operator[](long long index) const{
        return GetElement(index);
    }

    T& operator[](long long index) {
        return GetElement(index);
    }
};
