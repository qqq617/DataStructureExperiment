#pragma once
#include<cstddef>
#include<stdexcept>
template<typename T>
class LinkQueue{
private:
    struct Node
    {
        T value;
        Node* next;
    };
    
    Node* first_;
    Node* last_;
    std::size_t size_;

public:
    LinkQueue() : first_(nullptr), last_(nullptr), size_(0){}

    ~LinkQueue() {
        while(first_ != nullptr){
            Node* old = first_;
            first_ = first_->next;
            delete old;
        }
    }

    bool empty() const {
        return first_ == nullptr;
    }

    std::size_t size() const {
        return size_;
    }

    const T& first() const {
        if(empty()){
            throw std::out_of_range("Queue is empty");
        }
        return first_->value;
    }

    void push(const T& value){
        Node* n = new Node{value,nullptr};
        if(last_ == nullptr){
            first_ = n;
        }else{
            last_->next = n;
        } 

        last_ = n;
        size_++;
    }

    T pop(){
        if(empty()){
            throw std::out_of_range("Queue is empty");
        }
        Node* n = first_;
        T value = n->value;
        first_ = first_->next;
        if(first_ == nullptr) last_ = nullptr;
        delete n;
        size_--;
        return value;
    }
};