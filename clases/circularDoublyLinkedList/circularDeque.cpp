#include <iostream>

template <typename T>
class circularDeque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    int MAX_SIZE;
    Node* front;
    Node* rear;

public:
    circularDeque(int size) {
        MAX_SIZE = size;
        Node* prev = nullptr;
        Node* tail = nullptr;
        Node* new_node = new Node();
        new_node->prev = prev;
        Node* head = new_node;
        for (int i = 1; i < MAX_SIZE; i++) {
            Node* new_node = new Node();
            new_node->prev = prev;
            prev->next = new_node;
            tail = new_node;
        }
        tail->next = head;<
        head->prev = tail;
    }

    ~circularDeque() {
        clear();
    }

    void clear() {
        Node* current = front;
        Node* next;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        front = rear = nullptr;
    }

    push_front(T value) {
        if (isFull()) {
            return;
        }
        Node* new_node = new Node();
        new_node->data = value;
        new_node->next = front;
        new_node->prev = rear;
        front->prev = new_node;
        rear->next = new_node;
        front = new_node;
    }



    void print() const {

    }
};

int main() {
    CircularDoublyLinkedList<int> list;

    return 0;
}