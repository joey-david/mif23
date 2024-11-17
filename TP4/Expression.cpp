#include "Expression.h"

Constante::Constante(int val) : val(val) {}

int Constante::eval() const {
    return val;
}

Expression* Constante::clone() const {
    return new Constante(val);
}

Plus::Plus(const Expression& left, const Expression& right) {
    this->left = left.clone();
    this->right = right.clone();
}

Plus::~Plus() {
    delete left;
    delete right;
}

int Plus::eval() const {
    return left->eval() + right->eval();
}

Expression* Plus::clone() const {
    return new Plus(*left, *right);
}

Moins::Moins(const Expression& left, const Expression& right) {
    this->left = left.clone();
    this->right = right.clone();
}

Moins::~Moins() {
    delete left;
    delete right;
}

int Moins::eval() const {
    return left->eval() - right->eval();
}

Expression* Moins::clone() const {
    return new Moins(*left, *right);
}

Mult::Mult(const Expression& left, const Expression& right) {
    this->left = left.clone();
    this->right = right.clone();
}

Mult::~Mult() {
    delete left;
    delete right;
}

int Mult::eval() const {
    return left->eval() * right->eval();
}

Expression* Mult::clone() const {
    return new Mult(*left, *right);
}

int main() {
    int a = 5;
    const Expression & e = Mult(Plus(Constante(a), Constante((-2))), Plus(Constante(1), Constante(3)));
    std::cout << e.eval() << std::endl;
    return 0;
}