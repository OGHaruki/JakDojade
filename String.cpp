#include <cstring>
#include <iostream>
#include "String.h"
using namespace std;

String::String() {
    string_length = 0;
    data = nullptr;
}

String::String(const String &str) {
    data = nullptr;
    string_length = 0;
    const String* strPointer = &str;
    for(int i = 0; i < str.string_length; i++) {
        PushBack(str[i]);
    }
}

String::~String() {
    delete[] data;
    string_length = 0;
}

int String::GetLength() {
    return string_length;
}

char& String::operator[](int index) {
    return data[index];
}

const char &String::operator[](int index) const {
    return data[index];
}

ostream& operator<<(ostream& os, const String& str) {
    for(int i = 0; i < str.string_length; i++) {
        os << str.data[i];
    }
    return os;
}

bool operator==(String& str1, const char* str2) {
    for(int i = 0; i < strlen(str2); i++) {
        if(i >= str1.string_length) return false;
        if(str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

bool operator==(const String& str1, const String& str2) {
    if(str1.string_length != str2.string_length)
        return false;
    for(int i = 0; i < str1.string_length; i++) {
        if(str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

String& String::operator=(const char *right) {
    int length = strlen(right);
    delete[] data;
    data = new char[length + 1];
    for(int i = 0 ; i < length; i++) {
        data[i] = right[i];
    }
    data[length] = '\0';
    return *this;
}

String& String::operator=(const String &right) {
    if(this == &right) {
        return *this;
    }
    String pom = right;
    std::swap(data, pom.data);
    string_length = pom.string_length;
    return *this;
}

String& String::operator+=(const char right) {
    int length = string_length + 1;
    char* new_data = new char[length + 1];
    for(int i = 0; i < string_length; i++) {
        new_data[i] = data[i];
    }
    int pom = 0;
    new_data[length-1] = right;
    new_data[length] = '\0';
    swap(data, new_data);
    delete[] new_data;
    return *this;
}

void String::PushBack(const char c) {
    if(data == nullptr) {
        data = new char[1];
    }
    int length = string_length;
    string_length++;
    char * new_data = new char[length + 2];
    for(int i = 0; i < length; i++) {
        new_data[i] = data[i];
    }
    new_data[length] = c;
    new_data[length + 1] = '\0';
    swap(data, new_data);
    delete[] new_data;
}

void String::Clear() {
    delete[] data;
    data = nullptr;
    string_length = 0;
}

void String::DeleteLast() {
    char * new_string = new char[string_length];
    for(int i = 0; i < string_length - 1; i++) {
        new_string[i] = data[i];
    }
    new_string[string_length - 1] = '\0';
    swap(data, new_string);
    delete[] new_string;
    string_length--;
}

void String::DeleteFirst() {
    char * tmp = new char[string_length];
    for(int i = 0; i < string_length - 1; i++) {
        tmp[i] = data[i+1];
    }
    tmp[string_length - 1] = '\0';
    swap(data, tmp);
    delete[] tmp;
    string_length--;
}
