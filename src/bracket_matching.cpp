#include<LinkedStack.hpp>
#include<string>
using namespace std;
bool isMatchingPair(char left,char right){
    if(left == '('){
        if(right == ')'){
            return true;
        }
    }else if (left == '{')
    {
        if(right == '}'){
            return true;
        }
    }else if (left == '[')
    {
        if(right == ']'){
            return true;
        }
    }

    return false;    
}

bool isBalanced(const string& expression){
    LinkedStack<char> stack;

    for(char ch : expression){
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push(ch);
        }else if(ch == ')' || ch == ']' || ch == '}'){
            if(stack.empty()){
                return false;
            }

            if(isMatchingPair(stack.top(),ch)){
                stack.pop();
            }else{
                return false;
            }
        }
    }
    
    return stack.empty();
}