#ifndef TABLEAU_H
#define TABLEAU_H

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iostream>

template <typename T, size_t AGRANDISSEMENT = 10>
class Tableau;  // Forward declaration

template <typename T, size_t AGRANDISSEMENT = 10>
class TabIterator {
private:
    Tableau<T, AGRANDISSEMENT>& tableau;
    size_t currentIndex;

public:
    // Constructor
    TabIterator(Tableau<T, AGRANDISSEMENT>& tab, size_t index) 
        : tableau(tab), currentIndex(index) {}

    // Dereference operator
    T& operator*() {
        return tableau[currentIndex];
    }

    // Pre-increment
    TabIterator& operator++() {
        ++currentIndex;
        return *this;
    }

    // Post-increment
    TabIterator operator++(int) {
        TabIterator temp = *this;
        ++currentIndex;
        return temp;
    }

    // Equality comparison
    bool operator!=(const TabIterator& other) const {
        return &tableau != &(other.tableau) || currentIndex != other.currentIndex;
    }

    // Equality comparison
    bool operator==(const TabIterator& other) const {
        return &tableau == &(other.tableau) && currentIndex == other.currentIndex;
    }
};

template <typename T, size_t AGRANDISSEMENT>
class Tableau {
private:
    size_t size;
    size_t capacity;
    T* ptr;

    void grow() {
        capacity += AGRANDISSEMENT;
        T* newPtr = new T[capacity];
        std::copy(ptr, ptr + size, newPtr);
        delete[] ptr;
        ptr = newPtr;
    }

public:
    // Constructors
    Tableau() : size(0), capacity(AGRANDISSEMENT), ptr(new T[AGRANDISSEMENT]) {}
   
    explicit Tableau(size_t initialSize) : 
        size(initialSize), 
        capacity(initialSize + AGRANDISSEMENT), 
        ptr(new T[capacity]) {
            for (size_t i = 0; i < size; i++)
                ptr[i] = T();
        }

    Tableau(const T* arr, const size_t& otherSize) :
        ptr(new T[otherSize + AGRANDISSEMENT]),
        size(otherSize), 
        capacity(otherSize + AGRANDISSEMENT) {
        std::copy(arr, arr + size, ptr);
    }
    
    // Copy constructor
    Tableau(const Tableau<T, AGRANDISSEMENT>& tab) : 
        ptr(new T[tab.capacity]), 
        size(tab.size), 
        capacity(tab.capacity) {
        std::copy(tab.ptr, tab.ptr + tab.size, ptr);
    }

    // Assignment operator
    Tableau& operator=(const Tableau<T, AGRANDISSEMENT>& tab) {
        if (this != &tab) {
            delete[] ptr;
            size = tab.size;
            capacity = tab.capacity;
            ptr = new T[capacity];
            std::copy(tab.ptr, tab.ptr + size, ptr);
        }
        return *this;
    }

    // Destructor
    ~Tableau() {
        delete[] ptr;
    }

    // Add element
    void add(T obj) {
        if (size + 1 > capacity) grow();
        ptr[size] = obj;
        size++;
    }

    // Subscript operator
    T& operator[](size_t ind) {
        if (ind >= size) throw std::out_of_range("Index out of range");
        return ptr[ind];
    }

    const T& operator[](size_t ind) const {
        if (ind >= size) throw std::out_of_range("Index out of range");
        return ptr[ind];
    }

    // Stream input operator
    friend std::istream& operator>>(std::istream& is, Tableau<T, AGRANDISSEMENT>& tab) {
        T temp;
        while (is >> temp) {
            tab.add(temp);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tableau<T, AGRANDISSEMENT>& tab) {
        for (size_t i = 0; i < tab.size; i++) {
            os << tab.ptr[i] << " ";
        }
        return os;
    }

    // Iterator methods
    TabIterator<T, AGRANDISSEMENT> begin() {
        return TabIterator<T, AGRANDISSEMENT>(*this, 0);
    }

    TabIterator<T, AGRANDISSEMENT> end() {
        return TabIterator<T, AGRANDISSEMENT>(*this, size);
    }

    // Getters
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
};

#endif // TABLEAU_H