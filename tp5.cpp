#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <iterator>

class Template {
public:
    template <typename T>
    static void mySwap(T& a, T& b) {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }

    template <typename T>
    static T myMin(const T& a, const T& b) {
        return a < b ? a : b;
    }

    static std::string myMin(const std::string& a, const std::string& b) {
        return a < b ? a : b;
    }

    template <size_t I>
    static const char* myMin(const char(&a)[I], const char (&b)[I]) {
        return std::strcmp(a, b) < 0 ? a : b;
    }
};

template <typename T, size_t AGRANDISSEMENT = 10>
class Tableau {
public:
    Tableau() : data(new T[AGRANDISSEMENT]), size(0), capacity(AGRANDISSEMENT) {}

    Tableau(const T* other, size_t size) : data(new T[size]), size(size), capacity(size) {
        std::copy(other, other + size, data);
    }

    explicit Tableau(const Tableau<T>& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        std::copy(other.data, other.data + size, data);
    }

    Tableau& operator=(const Tableau<T>& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.capacity];
            size = other.size;
            capacity = other.capacity;
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    T& operator[](const int index){
        if (abs(index) >= size) {
            std::cout << "eh oh";
            return data[size-1];
        }
        else if (index < 0) {
            return data[size + index];
        }
        
        return data[index];
    }

    T operator[](const int index) const {
        if (abs(index) >= size) {
            std::cout << "eh oh";
            return data[size-1];
        }
        else if (index < 0) {
            return data[size + index];
        }
        
        return data[index];
    }

    ~Tableau() {
        delete[] data;
    }

    void push_back(const T& elt) {
        if (size == capacity) grow();
        data[size] = elt;
        size++;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tableau<T>& tableau) {
        for (int i = 0; i < tableau.size; ++i) os << tableau.data[i] << " ";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Tableau<T>& tableau) {
        T elt;
        is >> elt;
        tableau.push_back(elt);
        return is;
    }

    class evenIterator {
    private:
        T* ptr;
        size_t index;

    public:
        evenIterator(T* p = nullptr, size_t i = 0) : ptr(p), index(i) {}
        
        T& operator*() { return *ptr; }
        
        evenIterator& operator++() {
            ptr += 2;
            index += 2;
            return *this;
        }
        
        evenIterator operator++(int) {
            evenIterator tmp = *this;
            ptr += 2;
            index += 2;
            return tmp;
        }
        
        bool operator==(const evenIterator& other) const {
            return index >= other.index;
        }
        
        bool operator!=(const evenIterator& other) const {
            return index < other.index;
        }
    };

    // Insertor class definition
    class Insertor {
    public:
        using iterator_category = std::output_iterator_tag;
        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;

        Insertor(Tableau<T, AGRANDISSEMENT>* container) : container(container) {}

        Insertor& operator*() { return *this; }
        
        Insertor& operator++() { return *this; }
        Insertor& operator++(int) { return *this; }

        Insertor& operator=(const T& value) {
            container->push_back(value);
            return *this;
        }

    private:
        Tableau<T, AGRANDISSEMENT>* container;
    };
        // Const iterator methods
        const Iterator begin() const { return Iterator(data); }
        const Iterator end() const { return Iterator(data + size); }

        // Insertor method
        Insertor insertor() { return Insertor(this); }

    private:
        T* data;
        size_t size;
        size_t capacity;

        void grow() {
            capacity += AGRANDISSEMENT;
            T* newData = new T[capacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
        }
    };

int main() {
    Tableau<int> t;
    
    // Using push_back
    t.push_back(1);
    t.push_back(2);
    t.push_back(3);

    // Using iterator to traverse
    std::cout << "Using iterator: ";
    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using range-based for loop (works because we have begin/end)
    std::cout << "Using range-based for: ";
    for (const auto& element : t) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Using insertor
    auto ins = t.insertor();
    *ins = 4;  // Inserts 4 at the end
    *ins = 5;  // Inserts 5 at the end

    // Can also use with algorithms
    std::vector<int> v = {6, 7, 8};
    std::copy(v.begin(), v.end(), t.insertor());
    std::cout << "After insertor: " << t << std::endl;
    return 0;
}