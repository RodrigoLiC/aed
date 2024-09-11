#include <iostream>

using namespace std;

class Stack {
private:
    char* arr;
    int MAX_SIZE;
    int top;
    int cant_max_alcanzada;
public:
    Stack(int size) : MAX_SIZE(size), top(-1) {
        arr = new char[MAX_SIZE];
        cant_max_alcanzada = 0;
    }
    ~Stack() {
        delete[] arr;
    }
    bool isEmpty() const {
        return top == -1;
    }
    void push(char c) {
        arr[++top] = c;
        int cantidad_actual = (top + 1);
        if (cantidad_actual > cant_max_alcanzada) {
            cant_max_alcanzada = cantidad_actual;
        }
    }
    char pop() {
        return arr[top--];
    }
    int get_max_top() {
        return cant_max_alcanzada;
    }
};

int (const string& s) {

}
int main() {

    return 0;
}