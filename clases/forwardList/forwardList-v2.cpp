#include <iostream>
#include <list>

using namespace std;

template <typename T>
class List {
private:
    struct Node {
        T* data;
        Node* next;
    };
    Node* head;
    Node* merge(Node* first, Node* second) {
        if (!first) { return second; }
        if (!second) { return first; }

        if (*first->data < *second->data) {
            first->next = merge(first->next,second);
            return first;
        } else {
            second->next = merge(first,second->next);
            return second;
        }
    }
    Node* mergeSort(Node* begin) {
        if (!begin || !begin->next)
            return begin;
        Node* slow = begin;
        Node* fast = begin->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* half = slow->next;
        slow->next = nullptr;
        return merge(mergeSort(begin), mergeSort(half));
    }
public:
    List(){
        head = nullptr;
    }
    ~List() {
        clear();
    }
    T front(){
        if(head != nullptr){
            return *head->data;
        }
        return T();
    }
    T back(){
        if(head != nullptr){
            Node* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            return *temp->data;
        }
        return T();
    }
    // Method to push raw values (creates a new object dynamically)
    void push_front(const T& value) {
        Node* newNode = new Node();
        newNode->data = new T(value);  // Dynamically allocate memory for the value
        newNode->next = head;
        head = newNode;
    }
    // Method to push pointers (points to existing objects)
    void push_front(T* valuePtr) {
        Node* newNode = new Node();
        newNode->data = valuePtr;
        newNode->next = head;
        head = newNode;
    }
    void push_front (List& list){
        Node* temp = list.getHead();
        while(temp != nullptr){
            push_front(temp->data);
            temp = temp->next;
        }
    }
    void push_back(const T& value) {
        Node* newNode = new Node();
        newNode->data = new T(value);
        newNode->next = nullptr;
        if(!head){
            head = newNode;
        }else{
            Node* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void push_back(T* valuePtr) {
        Node* newNode = new Node();
        newNode->data = valuePtr;
        newNode->next = nullptr;
        if(!head){
            head = newNode;
        }else{
            Node* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void push_back(List& list){
        Node* temp = list.getHead();
        while(temp != nullptr){
            push_back(temp->data);
            temp = temp->next;
        }
    }
    T pop_front(){
        if(head){
            Node* temp = head;
            head = head->next;
            T data = *head->data;
            delete temp;
            return data;
        }
        return T();
    }
    T pop_back(){
        if(head){
            Node* temp = head;
            Node* prev = nullptr;
            while(temp->next != nullptr){
                prev = temp;
                temp = temp->next;
            }
            if(prev){
                prev->next = nullptr;
            }else{
                head = nullptr;
            }
            T data = *temp->data;
            delete temp;
            return data;
        }
        return T();
    }
    T operator[](int index){
        if(head != nullptr){
            Node* temp = head;
            for(int i = 0; i < index; i++){
                if(temp->next == nullptr){
                    return T();
                }
                temp = temp->next;
            }
            return *temp->data;
        }
        return T();
    }
    bool isEmpty(){
        return head == nullptr;
    }
    void insert(int index, const T& data){
        if(index == 0){
            push_front(data);
        }else{
            Node* temp = head;
            for(int i = 0; i < index - 1; i++){
                if(temp->next == nullptr){
                    return;
                }
                temp = temp->next;
            }
            Node* newNode = new Node();
            newNode->data = new T(data);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    void insert(int index, T* dataPtr){
        if(index == 0){
            push_front(dataPtr);
        }else{
            Node* temp = head;
            for(int i = 0; i < index - 1; i++){
                if(temp->next == nullptr){
                    return;
                }
                temp = temp->next;
            }
            Node* newNode = new Node();
            newNode->data = dataPtr;
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    void remove(int index){
        if(head != nullptr){
            if(index == 0){
                pop_front();
            }else{
                Node* temp = head;
                for(int i = 0; i < index - 1; i++){
                    if(temp->next == nullptr){
                        return;
                    }
                    temp = temp->next;
                }
                if(temp->next != nullptr){
                    Node* toDelete = temp->next;
                    temp->next = toDelete->next;
                    delete toDelete;
                }
            }
        }
    }
    int size(){
        int count = 0;
        Node* temp = head;
        while(temp != nullptr){
            temp = temp->next;
            count++;
        }
        return count;
    }
    void clear(){
        while(head != nullptr){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void sort() {
        head = mergeSort(head);
    }
    void reverse(){
        if(head != nullptr){
            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;
            while(current != nullptr){
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }
    }

    void swap(int index1, int index2){
        if(index1 == index2){
            return;
        }
        if(index1 > index2){
            int temp = index1;
            index1 = index2;
            index2 = temp;
        }
        Node* temp = head;
        Node* prev1 = nullptr;
        Node* prev2 = nullptr;
        for(int i = 0; i < index2; i++){
            if(i == index1-1){
                prev1 = temp;
            }
            if(i == index2-1){
                prev2 = temp;
            }
            temp = temp->next;
            if (temp == nullptr){
                return;
            }
        }
        if(index1 == 0) {
            if(index2 - index1 > 1){
                temp = head->next;
                head->next = prev2->next->next;
                prev2->next->next = temp;
                temp = prev2->next;
                prev2->next = head;
                head = temp;
            }
            else {
                temp = head->next->next;
                head = prev2->next;
                head->next = prev2;
                prev2->next = temp;
            }
        } else if(index2 - index1 == 1){
            prev1->next = prev2->next;
            prev2->next = prev2->next->next;
            prev1->next->next = prev2;
        }
        else {
            temp = prev1->next->next;
            prev1->next->next = prev2->next->next;
            prev2->next->next = temp;
            temp = prev2->next;
            prev2->next = prev1->next;
            prev1->next = temp;
        }
    }

    Node *getHead(){
        return head;
    }

    friend ostream& operator<<(ostream& os, List<T>& list){
        Node* temp = list.head;
        os << "[";
        while(temp != nullptr){
            os << *(temp->data);
            if (temp->next != nullptr){
                os << ", ";
            }
            temp = temp->next;
        }
        os << "]";
        return os;
    }
};

void testEmpty(){
    List<string> results;
    List<int> list;
    cout << "Test empty: " << list << endl;
    results.push_back(list.isEmpty() ? "pass" : "fail");
    results.push_back(list.size() == 0 ? "pass" : "fail");
    results.push_back(list.front() == 0 ? "pass" : "fail");
    results.push_back(list.back() == 0 ? "pass" : "fail");
    results.push_back(list.pop_front() == 0 ? "pass" : "fail");
    results.push_back(list.pop_back() == 0 ? "pass" : "fail");
    results.push_back(list[-10] == 0 ? "pass" : "fail");
    results.push_back(list[0] == 0 ? "pass" : "fail");
    results.push_back(list[5] == 0 ? "pass" : "fail");
    cout << results << endl;
}

void testTransformation(){
    List<string> results;
    List<int> list;
    for (int i = 9; i > 0; i--){
        list.push_front(i);
    }
    cout << "Test transformation: " << list << endl;
    results.push_back(list.isEmpty() ? "fail" : "pass");
    results.push_back(list.size() == 9 ? "pass" : "fail");
    results.push_back(list.front() == 1 ? "pass" : "fail");
    results.push_back(list.back() == 9 ? "pass" : "fail");
    list.swap(0,8);
    cout << "Test swap: " << list << "( 0 <-> 8 )" << endl;
    list.swap(0,1);
    cout << "Test swap: " << list << "( 0 <-> 1 )" << endl;
    list.swap(4,7);
    cout << "Test swap: " << list << "( 4 <-> 7 )" << endl;
    list.swap(4,5);
    cout << "Test swap: " << list << "( 4 <-> 5 )" << endl;
    list.sort();
    cout << "Test sort: " << list << endl;
    list.reverse();
    cout << "Test reverse: " << list << endl;
    list.pop_back();
    list.pop_front();
    cout << "Test pop (front and back): " << list << endl;
    list.remove(3);
    cout << "Test remove (index 3): " << list << endl;
}


int main(){
    testEmpty();
    testTransformation();


    return 0;
}