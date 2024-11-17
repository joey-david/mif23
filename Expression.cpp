#include <iostream>
#include <memory>

class Expression {
public:
    virtual int eval() const = 0; //virtual sets as determined to be overridden
    virtual Expression* clone() const = 0; //=0 means pure virtual, no def here
    virtual ~Expression() = default;

    //Bloquer le mécanisme de copie
    Expression(const Expression&) = delete;//explain
    Expression& operator=(const Expression&) = delete; //explain
    Expression(Expression&&) = delete;//explain
    Expression& operator=(Expression&&) = delete; //explain

protected:
    Expression() = default; //explain
};

class Constante : public Expression {
private:
    int value;

public:
    explicit Constante(int val) : value(val) {};

    int eval() const override { //explain
        return value; //explain
    }

    Expression* clone() const override { //explain
        return new Constante(value);
    }
};

class ExpressionBinaire : public Expression {
protected: 
    std::unique_ptr<Expression> left; //explain
    std::unique_ptr<Expression> right; //explain

public:
    ExpressionBinaire(const Expression& l, const Expression& r) //explain
        : left(l.clone()), right(r.clone()) {}
};

class Plus : public ExpressionBinaire {
public:
    using ExpressionBinaire::ExpressionBinaire;

    int eval() const override {
        return left->eval() + right->eval();
    }

    Expression* clone() const override { //explain
        return new Plus(*left, *right); //explain
    }
};

class Times : public ExpressionBinaire {
public:
    using ExpressionBinaire::ExpressionBinaire;

    int eval() const override {
        return left->eval() * right->eval();
    }

    Expression* clone() const override { //explain
        return new Times(*left, *right); //explain
    }
};

class Minus : public ExpressionBinaire {
public:
    using ExpressionBinaire::ExpressionBinaire;

    int eval() const override {
        return left->eval() - right->eval();
    }

    Expression* clone() const override { //explain
        return new Minus(*left, *right); //explain
    }
};

int main() {
    int a = 5;
    const Expression& e = Times(Plus(Constante(a), Constante((-2))),Minus(Constante(a),Constante(3)));
    std::cout << e.eval() << std::endl;
}