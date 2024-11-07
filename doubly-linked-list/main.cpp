//
//  main.cpp
//  doubly-linked-list
//
//  Created by Godswill Adigwe on 07/11/2024.
//

#include <iostream>

struct Node {
    Node* prev;
    int data;
    Node* next;
    
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    
public:
    DoublyLinkedList():head(nullptr), tail(nullptr){}
    
    void append(int data) {
        
        Node* newNode = new Node(data);
        
        if(!head){
            head = tail = newNode;
        }else{
            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;
        }
    }
    
    void displayForward() {
        Node* current = head;
        
        while(current) {
            std::cout << current -> data << " -> ";
            current = current -> next;
        }
        std::cout << "null" << std::endl;
    }
    
    void displayBackward() {
        Node* current = tail;
        
        while(current) {
            
            std::cout << current -> data << " -> ";
            current = current -> prev;
        }
        
        std::cout << "null" << std::endl;
    }
    
};

int main(int argc, const char * argv[]) {

    DoublyLinkedList list;
    list.append(10);
    list.append(20);
    list.append(30);
    
    list.displayForward();
    list.displayBackward();
    return 0;
}
