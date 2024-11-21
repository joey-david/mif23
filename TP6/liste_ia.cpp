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
class ListeTriee {
private:
    std::unique_ptr<Cellule<T>> head; // First cell
    Cellule<T>* tail;                 // Last cell (not unique_ptr for simplicity)

public:
    // Constructor
    ListeTriee() : head(nullptr), tail(nullptr) {}

    // Copy Constructor
    ListeTriee(const ListeTriee& other) {
        for (Cellule<T>* current = other.head.get(); current != nullptr; current = current->next.get()) {
            ajouter(current->data);
        }
    }

    // Move Constructor
    ListeTriee(ListeTriee&& other) noexcept 
        : head(std::move(other.head)), tail(other.tail) {
        other.tail = nullptr;
    }

    // Copy Assignment
    ListeTriee& operator=(const ListeTriee& other) {
        if (this == &other) return *this;
        ListeTriee temp(other);
        *this = std::move(temp);
        return *this;
    }

    // Move Assignment
    ListeTriee& operator=(ListeTriee&& other) noexcept {
        if (this == &other) return *this;
        head = std::move(other.head);
        tail = other.tail;
        other.tail = nullptr;
        return *this;
    }

    // Add an element (sorted insertion)
    void ajouter(const T& value) {
        auto newCell = std::make_unique<Cellule<T>>(value);

        if (!head) {
            // If the list is empty
            tail = newCell.get();
            head = std::move(newCell);
        } else if (value <= head->data) {
            // Insert at the beginning
            newCell->next = std::move(head);
            head = std::move(newCell);
        } else {
            // Insert in sorted order
            Cellule<T>* current = head.get();
            while (current->next && current->next->data < value) {
                current = current->next.get();
            }
            newCell->next = std::move(current->next);
            current->next = std::move(newCell);

            if (!current->next->next) {
                // Update tail if necessary
                tail = current->next.get();
            }
        }
    }

    // Print the list
    void afficher() const {
        Cellule<T>* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    // Destructor
    ~ListeTriee() = default;
};


// Example usage
int main() {
    ListeTriee<int> liste;

    liste.ajouter(10);
    liste.ajouter(5);
    liste.ajouter(20);
    liste.ajouter(15);

    std::cout << "Liste triee : ";
    liste.afficher();

    ListeTriee<int> copie = liste; // Copy
    std::cout << "Copie de la liste : ";
    copie.afficher();

    ListeTriee<int> deplace = std::move(liste); // Move
    std::cout << "Liste deplacee : ";
    deplace.afficher();

    return 0;
}