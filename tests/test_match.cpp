#include <cassert>
#include <iostream>
#include <string>

bool isBalanced(const std::string& expression);

int main() {
    assert(isBalanced("([]{})") == true);
    assert(isBalanced("([)]") == false);
    assert(isBalanced("((()))") == true);
    assert(isBalanced("((()") == false);
    assert(isBalanced("())") == false);
    assert(isBalanced("a + (b * c)") == true);
    assert(isBalanced("") == true);

    std::cout << "All tests passed!\n";
    return 0;
}