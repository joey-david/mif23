#include <iostream>

template <typename T>
class Noeud {
public:
    Noeud(T _val) : val(_val), fg(nullptr), fd(nullptr) {}

    ~Noeud() {
        delete fg;
        delete fd;
    }

    const T& getVal() const {
        return val;
    }

    void setVal(T _val) {
        val = _val;
    }

    Noeud* getFg() {
        return fg;
    }

    void setFg(Noeud* _fg) {
        fg = _fg;
    }

    Noeud* getFd() {
        return fd;
    }

    void setFd(Noeud* _fd) {
        fd = _fd;
    }

    void inserer(T _val) {
        if(_val < val) {
            if (fg == nullptr) {
                fg = new Noeud(_val);
            } else {
                fg->inserer(_val);
            }
            return;
        }
        if (fd == nullptr) {
            fd = new Noeud(_val);
        } else {
            fd->inserer(_val);
        }
    }

    bool recherche(T _val) {
        if (_val == val) {
            return true;
        }
        if (_val < val) {
            if(fg == nullptr) {
                return false;
            }
            return fg->recherche(_val);
        }
        if (fd == nullptr) {
            return false;
        }
        return fd->recherche(_val);
    }

    friend std::ostream& operator<<(std::ostream& os, const Noeud& noeud) {
        if(noeud.fg != nullptr) {
            os << *noeud.fg;
        }
        os << noeud.val << " ";
        if(noeud.fd != nullptr) {
            os << *noeud.fd;
        }
        return os;
    }
private:
    T val;
    Noeud* fg;
    Noeud* fd;
};