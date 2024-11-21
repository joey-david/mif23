#include <iostream>
#include <memory> // for std::unique_ptr

template <typename T>
class Cellule {
public:
    T data;
    std::unique_ptr<Cellule<T>> next;

    // Constructor
    Cellule(const T& value) : data(value), next(nullptr) {}

    // Destructor
    ~Cellule() = default;
};

template <typename T>
class Liste {
private:
    std::unique_ptr<Cellule<T>> head; // First cell
    Cellule<T>* tail;                 // Last cell (not unique_ptr for simplicity)

public:
    // Constructor
    Liste() : head(nullptr), tail(nullptr) {}

    // Add an element at the end
    void ajouter_fin(const T& value) {
        auto newCell = std::unique_ptr<Cellule<T>>(new Cellule<T>(value));
        if (!head) {
            // If the list is empty
            tail = newCell.get();
            head = std::move(newCell);
        } else {
            tail->next = std::move(newCell);
            tail = tail->next.get();
        }
    }

    // Nested Iterator class
    class Iterator {
    private:
        Cellule<T>* current;

    public:
        // Constructor
        Iterator(Cellule<T>* start) : current(start) {}

        // Dereference operator for read/write access
        T& operator*() { return current->data; }

        // Pre-increment operator
        Iterator& operator++() {
            if (current) current = current->next.get();
            return *this;
        }

        // Equality operator
        bool operator==(const Iterator& other) const { return current == other.current; }

        // Inequality operator
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    // Begin and End functions
    Iterator begin() const { return Iterator(head.get()); }
    Iterator end() const { return Iterator(nullptr); }

    // Print the list (using iterator)
    void afficher() const {
        for (auto it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    // Destructor
    ~Liste() = default;
};

// Example usage
int main() {
    Liste<int> liste;

    // Adding elements to the list
    liste.ajouter_fin(10);
    liste.ajouter_fin(20);
    liste.ajouter_fin(30);

    std::cout << "Liste : ";
    liste.afficher();

    // Using the iterator to modify elements
    for (auto it = liste.begin(); it != liste.end(); ++it) {
        *it += 5; // Increment each element by 5
    }

    std::cout << "Liste apres modification : ";
    liste.afficher();

    return 0;
}
