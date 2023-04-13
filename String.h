#pragma once
#include <iostream>

using namespace std;

class String {
public:
    char * data;
    int string_length;

    // Operators
    friend bool operator==(String& str1, const char* str2); //done
    friend bool operator==(const String& str1, const String& str2);
    friend ostream& operator<<(ostream& os, const String& str); // done
    String& operator=(const char *right); // done
    String& operator=(const String& _other);
    String& operator+=(const char right);
    char& operator[](int index);    // done
    const char& operator[](int index) const;

    // Constructors & destructor
    String();   // done
    String(const String& data);
    ~String();  // done

    // Functions
    void PushBack(char c);
    void Clear();
    void DeleteLast();
    void DeleteFirst();
    int GetLength();
};
