#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <memory> // for std::unique_ptr

class Expression {
public:
    Expression() { std::cout << "Expression default constructor\n"; }
    virtual int eval() const = 0;
    virtual std::unique_ptr<Expression> clone() const = 0;
    virtual ~Expression() { std::cout << "Expression destructor\n"; }

    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;

    Expression(Expression&&) noexcept = default;
    Expression& operator=(Expression&&) noexcept = default;
};

class Constante : public Expression {
public:
    explicit Constante(int val) : val(val) {
        std::cout << "Constante constructor\n";
    }

    int eval() const override { return val; }

    std::unique_ptr<Expression> clone() const override {
        std::cout << "Cloning Constante\n";
        return std::make_unique<Constante>(val);
    }

    ~Constante() { std::cout << "Constante destructor\n"; }

private:
    int val;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {
        std::cout << "BinaryExpression constructor\n";
    }

    ~BinaryExpression() { std::cout << "BinaryExpression destructor\n"; }

protected:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

class Plus : public BinaryExpression {
public:
    Plus(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : BinaryExpression(std::move(left), std::move(right)) {
        std::cout << "Plus constructor\n";
    }

    int eval() const override { return left->eval() + right->eval(); }

    std::unique_ptr<Expression> clone() const override {
        std::cout << "Cloning Plus\n";
        return std::make_unique<Plus>(left->clone(), right->clone());
    }

    ~Plus() { std::cout << "Plus destructor\n"; }
};

class Moins : public BinaryExpression {
public:
    Moins(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : BinaryExpression(std::move(left), std::move(right)) {
        std::cout << "Moins constructor\n";
    }

    int eval() const override { return left->eval() - right->eval(); }

    std::unique_ptr<Expression> clone() const override {
        std::cout << "Cloning Moins\n";
        return std::make_unique<Moins>(left->clone(), right->clone());
    }

    ~Moins() { std::cout << "Moins destructor\n"; }
};

class Mult : public BinaryExpression {
public:
    Mult(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : BinaryExpression(std::move(left), std::move(right)) {
        std::cout << "Mult constructor\n";
    }

    int eval() const override { return left->eval() * right->eval(); }

    std::unique_ptr<Expression> clone() const override {
        std::cout << "Cloning Mult\n";
        return std::make_unique<Mult>(left->clone(), right->clone());
    }

    ~Mult() { std::cout << "Mult destructor\n"; }
};

#endif // EXPRESSION_H