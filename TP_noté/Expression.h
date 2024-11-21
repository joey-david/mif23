#include <vector>

class Expression {
public:
    virtual float eval() const = 0;
    virtual float eval(std::vector<float> tab) const = 0;
    virtual Expression* clone() const = 0;
    virtual float evalDerivee(std::vector<float> tab, int index) const = 0;
    Expression() = default;
    virtual ~Expression() = default;
};

class Constante : public Expression {
public:
    virtual float eval() const override {
        return val;
    }

    virtual float eval(std::vector<float> tab) const override {
        return val;
    }

    virtual Expression* clone() const override {
        return new Constante(val);
    }

    virtual float evalDerivee(std::vector<float> tab, int index) const override {
        return 0.0f;
    }

    Constante(const float cst = 0) : val(cst) {}

private:
    float val;
};

class Variable : public Expression {
public:
    virtual float eval() const override {
        return index;
    }

    virtual float eval(std::vector<float> tab) const override {
        return tab[index];
    }

    virtual Expression* clone() const override {
        return new Variable(index);
    }

    virtual float evalDerivee(std::vector<float> tab, int varIndex) const override {
        return (index == varIndex) ? 1.0f : 0.0f;
    }

    Variable(const int _index = -1) : index(_index) {}

private:
    int index;
};

class Plus : public Expression {
public:
    virtual float eval() const override {
        return (expr1->eval() + expr2->eval());
    }

    virtual float eval(std::vector<float> tab) const override {
        return (expr1->eval(tab) + expr2->eval(tab));
    }

    virtual Expression* clone() const override {
        return new Plus(expr1->clone(), expr2->clone());
    }

    virtual float evalDerivee(std::vector<float> tab, int index) const override {
        return expr1->evalDerivee(tab, index) + expr2->evalDerivee(tab, index);
    }

    Plus(Expression* _expr1, Expression* _expr2) : expr1(_expr1), expr2(_expr2) {}

    ~Plus() override {
        delete expr1;
        delete expr2;
    }

private:
    Expression* expr1;
    Expression* expr2;
};

class Moins : public Expression {
public:
    virtual float eval() const override {
        return (expr1->eval() - expr2->eval());
    }

    virtual float eval(std::vector<float> tab) const override {
        return (expr1->eval(tab) - expr2->eval(tab));
    }

    virtual Expression* clone() const override {
        return new Moins(expr1->clone(), expr2->clone());
    }

    virtual float evalDerivee(std::vector<float> tab, int index) const override {
        return expr1->evalDerivee(tab, index) - expr2->evalDerivee(tab, index);
    }

    Moins(Expression* _expr1, Expression* _expr2) : expr1(_expr1), expr2(_expr2) {}

    ~Moins() override {
        delete expr1;
        delete expr2;
    }

private:
    Expression* expr1;
    Expression* expr2;
};

class Mult : public Expression {
public:
    virtual float eval() const override {
        return (expr1->eval() * expr2->eval());
    }

    virtual float eval(std::vector<float> tab) const override {
        return (expr1->eval(tab) * expr2->eval(tab));
    }

    virtual Expression* clone() const override {
        return new Mult(expr1->clone(), expr2->clone());
    }

    virtual float evalDerivee(std::vector<float> tab, int index) const override {
        return (expr1->eval(tab) * expr2->evalDerivee(tab, index)) + (expr1->evalDerivee(tab, index) * expr2->eval(tab));
    }

    Mult(Expression* _expr1, Expression* _expr2) : expr1(_expr1), expr2(_expr2) {}

    ~Mult() override {
        delete expr1;
        delete expr2;
    }

private:
    Expression* expr1;
    Expression* expr2;
};