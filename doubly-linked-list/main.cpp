//
//  main.cpp
//  doubly-linked-list
//
//  Created by Godswill Adigwe on 07/11/2024.
//

#include <iostream>

template <typename... T>
struct Node {
    Node<T...>* prev;
    std::variant<T...> data;
    Node<T...>* next;
    
    Node(std::variant<T...> value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename... T>
class DoublyLinkedList {
private:
    Node<T...>* head;
    Node<T...>* tail;
    
public:
    DoublyLinkedList():head(nullptr), tail(nullptr){}
    
    void append(std::variant<T...> data) {
        
        Node<T...>* newNode = new Node<T...>(data);
        
        if(!head){
            head = tail = newNode;
        }else{
            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;
        }
    }
    
    class Iterator {
    private:
        Node<T...>* current;
        
    public:
        Iterator(Node<T...>* node) : current(node) {}
        
        std::variant<T...>& operator*() const {
            return current->data;
        }
        
        Iterator& operator++() {
            if(current) current = current->next;
            return *this;
        }
        
        Iterator& operator--() {
            if(current) current = current->prev;
            return *this;
        }
        
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    
    void deleteNode(std::variant<T...> value) {
        Node<T...>* current = head;
        
        while (current != nullptr && current->data != value){
            current = current->next;
        }
        
        if(current == nullptr) {
            std::cout << "Node with value ";
            std::visit([](const auto& v) { std::cout << v; }, value);
            std::cout << " not found." << std::endl;
            return;
        }
        
        if(current == head) {
            head = head->next;
            
            if(head != nullptr) {
                head -> prev = nullptr;
            }else {
                tail = nullptr;
            }
        }else if(current == tail) {
            tail = tail -> prev;
            if(tail != nullptr) {
                tail->next = nullptr;
            }else {
                head = nullptr;
            }
        }else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        
        delete  current;
//        std::cout << "Node with value " << value << " deleted." << std::endl;
        std::cout << "Node with value ";
        std::visit([](const auto& v) { std::cout << v; }, value);
        std::cout << " deleted." << std::endl;
    }
    
    void displayForward() {
//        Node<T...>* current = head;
//
//        while(current) {
//            std::visit([](const auto& value) {std::cout << value << " -> ";}, current->data);
//            current = current -> next;
//        }
        
        for(Iterator it = begin(); it != end(); ++it) {
            std::visit([](auto& val) { std::cout << val << " -> "; }, *it);
        }
        std::cout << "null" << std::endl;
    }
    
    void displayBackward() {
//        Node<T...>* current = tail;
        
//        while(current) {
//            std::visit([](const auto& value) {std::cout << value << " -> ";}, current->data);
//            current = current -> prev;
//        }
        for(Iterator it = Iterator(tail); it != Iterator(nullptr); --it) {
            std::visit([](auto& val) { std::cout << val << " -> "; }, *it);
        }
        
        std::cout << "null" << std::endl;
    }
    
    ~DoublyLinkedList() {
        Node<T...>* current = head;
        while (current) {
            Node<T...>* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main(int argc, const char * argv[]) {

    DoublyLinkedList<int, std::string> list;
    list.append(10);
    list.append("Hello");
    list.append(30);
    list.displayForward();
    list.displayBackward();
    list.deleteNode(30);
    list.displayForward();
    list.displayBackward();
    
    
    return 0;
}
