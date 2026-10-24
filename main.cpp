#include <iostream>
#include <string>

bool isBalanced(const std::string& expression);

int main() {
    std::string expression;

    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    if (isBalanced(expression)) {
        std::cout << "Matched!" << std::endl;
    } else {
        std::cout << "Not matched!" << std::endl;
    }

    return 0;
}