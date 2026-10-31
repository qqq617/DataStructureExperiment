#include <cassert>
#include <cstdio>
#include "LinkedStack.hpp"

int main() {
    LinkedStack<int> stack;

    // Test 1: empty stack
    assert(stack.empty());
    assert(stack.size() == 0);

    // Test 2: push first element
    stack.push(10);
    assert(!stack.empty());
    assert(stack.size() == 1);
    assert(stack.top() == 10);

    // Test 3: push second element
    stack.push(20);
    assert(stack.size() == 2);
    assert(stack.top() == 20);

    std::printf("All push tests passed!\n");
    return 0;
}
