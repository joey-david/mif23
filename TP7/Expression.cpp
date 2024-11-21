
#include "Expression.h"

int main() {
    std::cout << "Starting program\n";

    int a = 5;
    auto expr = std::make_unique<Mult>(
        std::make_unique<Plus>(
            std::make_unique<Constante>(a),
            std::make_unique<Constante>(-2)
        ),
        std::make_unique<Plus>(
            std::make_unique<Constante>(1),
            std::make_unique<Constante>(3)
        )
    );

    std::cout << "Expression result: " << expr->eval() << std::endl;

    std::cout << "Ending program\n";
    return 0;
}