#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>

class Expression {
public:
    Expression() = default;
    virtual int eval() const = 0;
    virtual Expression* clone() const = 0;
    virtual ~Expression() = default;

    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
    Expression(Expression&&) = delete;
    Expression& operator=(Expression&&) = delete;
};

class Constante : public Expression {
public:
    explicit Constante(int val);
    int eval() const override;
    Expression* clone() const override;
private:
    int val;
};

class Plus : public Expression {
public:
    explicit Plus(const Expression& left, const Expression& right);
    ~Plus();
    int eval() const override;
    Expression* clone() const override;
protected:
    Expression* left;
    Expression* right;
};

class Moins : public Expression {
public:
    explicit Moins(const Expression& left, const Expression& right);
    ~Moins();
    int eval() const override;
    Expression* clone() const override;
protected:
    Expression* left;
    Expression* right;
};

class Mult : public Expression {
public:
    explicit Mult(const Expression& left, const Expression& right);
    ~Mult();
    int eval() const override;
    Expression* clone() const override;
protected:
    Expression* left;
    Expression* right;
};

#endif // EXPRESSION_H