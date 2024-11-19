#ifndef TABLEAU_H
#define TABLEAU_H
#include <algorithm>
#include <sstream>

//default param for size = 10
template <typename T, size_t AGRANDISSEMENT = 10>
class Tableau {
private:
    size_t size;
    size_t capacity;
    T* ptr;

    void grow(){
        capacity += AGRANDISSEMENT;
        T* newPtr = new T[capacity];
        std::copy(ptr, ptr + size, newPtr);
        delete[] ptr;
        ptr = newPtr;
    }

public:
    Tableau() : size(0), capacity(AGRANDISSEMENT), ptr(new T[AGRANDISSEMENT]) {}
    
    Tableau(const T* arr, const size_t& otherSize) : 
        ptr(new T[otherSize + AGRANDISSEMENT]), 
            size(otherSize), capacity(otherSize + AGRANDISSEMENT) {
        std::copy(arr, arr + size, ptr);
    }

    explicit Tableau(Tableau<T> &tab) : ptr(new T[tab.capacity]), size(tab.size), capacity(tab.capacity) {
        std::copy(tab.ptr, tab.ptr + tab.size, ptr);
    }

    Tableau& operator=(const Tableau<T>& tab) {
        if (this != &tab) {
            delete[] ptr;
            size = tab.size;
            capacity = tab.capacity;
            ptr = new Tableau[capacity];
            std::copy(tab.ptr, tab.ptr + size, ptr);
        }
        return *this;
    }

    ~Tableau() {
        delete[] ptr;
    }

    void add(T obj) {
        if (size + 1 > capacity) grow();
        ptr[size] = obj;
        size++;
    }

    const T& operator [](unsigned int& ind) {
        if (size <= ind) throw std::out_of_range("ind out of range");
        return ptr[ind];
    }
};

#endif