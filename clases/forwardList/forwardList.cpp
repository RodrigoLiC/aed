#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class List {
private:
    Node<T>* head;
public:
    List(){
        head = nullptr;
    }
    ~List() {
        clear();
    }
    T front(){
        if(head != nullptr){
            return head->data;
        }
        return T();
    }
    T back(){
        if(head != nullptr){
            Node<T>* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            return temp->data;
        }
        return T();
    }
    void push_front(T data){
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }
    void push_back(T data){
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;
        if(head == nullptr){
            head = newNode;
        }else{
            Node<T>* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    T pop_front(){
        if(head != nullptr){
            Node<T>* temp = head;
            head = head->next;
            T data = temp->data;
            delete temp;
            return data;
        }
        return T();
    }
    T pop_back(){
        if(head != nullptr){
            if(head->next == nullptr){
                T data = head->data;
                delete head;
                head = nullptr;
                return data;
            }else{
                Node<T>* temp = head;
                while(temp->next->next != nullptr){
                    temp = temp->next;
                }
                T data = temp->next->data;
                delete temp->next;
                temp->next = nullptr;
                return data;
            }
        }
        return T();
    }
    T operator[](int index){
        if(head != nullptr){
            Node<T>* temp = head;
            for(int i = 0; i < index; i++){
                if(temp->next == nullptr){
                    return T();
                }
                temp = temp->next;
            }
            return temp->data;
        }
        return T();
    }
    bool empty(){
        return head == nullptr;
    }
    int size(){
        int count = 0;
        Node<T>* temp = head;
        while(temp != nullptr){
            temp = temp->next;
            count++;
        }
        return count;
    }
    void clear(){
        while(head != nullptr){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void sort(){
        // cero elementos
        if(head == nullptr) {
            return;
        }
        // un elemento
        if(head->next == nullptr) {
            return;
        }
        // ordenar los dos primeros elementos
        if(head->data > head->next->data){
            head->next->next = head;
            head = head->next;
            head->next->next = nullptr;
        }
        // ordenar los demas elementos
        //TODO: mejorar el algoritmo
        Node<T>* temp = head;
        while(temp->next->next != nullptr){
            if(temp->next->data > temp->next->next->data){
                Node<T>* temp2 = temp->next;
                temp->next = temp->next->next;
                temp2->next = temp->next->next;
                temp->next->next = temp2;
                temp = head;
            }else{
                temp = temp->next;
            }
        }
    }
    void reverse(){
        if(head != nullptr){
            Node<T>* prev = nullptr;
            Node<T>* current = head;
            Node<T>* next = nullptr;
            while(current != nullptr){
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }
    }
};






int main(){
    // test lista vacia
    List<double> list1;
    cout << list1.front() << endl;
    cout << list1.back() << endl;
    cout << list1.pop_front() << endl;
    cout << list1.pop_back() << endl;
    cout << list1[3] << endl;
    cout << list1.size() << endl;
    // test push
    List<string> list2;
    list2.push_front("front1");
    list2.push_front("front2");
    list2.push_back("back1");
    list2.push_back("back2");
    cout << list2.front() << endl;
    cout << list2.back() << endl;
    // test []
    cout << "Imprimiendo " <<list2.size() << " elementos:"<< endl;
    for (int i = 0; i < list2.size(); i++){
        cout <<"- "<< list2[i] << endl;
    }

    // test pop
    cout << list2.pop_front() << endl;
    cout << list2.pop_back() << endl;
    cout << list2.front() << endl;

    // test clear
    list2.clear();
    cout << list2.size() << endl;

    // test reverse
    List<int> list3;
    list3.push_front(5);
    list3.push_front(4);
    list3.push_front(3);
    list3.push_front(2);
    list3.push_front(1);
    for (int i = 0; i < list3.size(); i++){
        cout << list3[i] << " ";
    }
    cout << "\n";
    list3.reverse();
    for (int i = 0; i < list3.size(); i++){
        cout << list3[i] << " ";
    }

    return 0;
}