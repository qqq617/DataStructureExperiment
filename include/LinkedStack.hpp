#pragma once
#include<cstddef>
#include<stdexcept>

template<typename T>
class LinkedStack{
private:
    struct Node
    {
        T value;
        Node* next;
    };
    
    Node* top_;
    std::size_t size_;

public:
    LinkedStack() : top_(nullptr), size_(0) {}

    ~LinkedStack() {
        while(top_ != nullptr){
            Node* old = top_;
            top_ = top_->next;
            delete old;
        }
    }

    bool empty() const {
        return top_ == nullptr;
    }

    std::size_t size() const {
        return size_;
    }

    const T& top() const {
        if(empty()){
            throw std::out_of_range("Stack is empty");
        }
        return top_->value;
    }
    
    void push(const T& value){
        Node* n = new Node{value,top_};
        top_ = n;
        size_++; 
    }

};
