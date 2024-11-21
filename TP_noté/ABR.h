#include "Noeud.h"
#include <stack>

template <typename T>
class ABR {
public:
    ABR() : racine(nullptr), taille(0) {}

    ~ABR() {
        delete racine;
    }

    unsigned int getTaille() {
        return taille;
    }

    void inserer(T val) {
        taille++;
        if(racine == nullptr) {
            racine = new Noeud(val);
            return;
        }
        racine->inserer(val);
    }

    bool recherche(T val) {
        return racine->recherche(val);
    }

    friend std::ostream& operator<<(std::ostream& os, const ABR& tree) {
        if(tree.racine == nullptr) {
            os << "[ ]";
        } else {
            os << "[ " << *tree.racine << "]";
        }
        return os;
    }

    class iterator {
    public:
        iterator(Noeud<T>* root = nullptr) : cur(root) {
            while (cur != nullptr) {
                pile.push(cur);
                cur = cur->getFg();
            }
            if(!pile.empty()) {
                cur = pile.top();            
            }
        }

        const T& operator*() const {
            return cur->getVal();
        }

        iterator& operator++() {
            if(pile.empty()) {
                cur = nullptr;
                return *this;
            }

            pile.pop();

            if(cur->getFd() != nullptr) {
                cur = cur->getFd();
                while (cur!= nullptr) {
                    pile.push(cur);
                    cur = cur->getFg();
                }
                if(!pile.empty()) {
                    cur = pile.top();
                }
            } else if (!pile.empty()) {
                cur = pile.top();
            } else {
                cur = nullptr;
            }
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return cur != other.cur;
        }
        
    private:
        Noeud<T>* cur;
        std::stack<Noeud<T>*> pile;
    };

    iterator begin() {
        return iterator(racine);
    }

    iterator end() {
        return iterator(nullptr);
    }



private:
    Noeud<T>* racine;
    unsigned int taille;
};