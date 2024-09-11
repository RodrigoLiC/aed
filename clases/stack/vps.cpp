#include <iostream>

using namespace std;

class Stack {
private:
    char* arr;
    int MAX_STACK_SIZE;
    int top;
    int greatest_depth_reached;
public:
    Stack(int size) : MAX_STACK_SIZE(size), top(-1) {
        arr = new char[MAX_STACK_SIZE];
        greatest_depth_reached = 0;
    }
    ~Stack() {
        delete[] arr;
    }
    bool isEmpty() const {
        return top == -1;
    }
    void push(char c) {
        arr[++top] = c;
        int current_depth = (top + 1);
        if (current_depth > greatest_depth_reached) {
            greatest_depth_reached = current_depth;
        }
    }
    char pop() {
        return arr[top--];
    }
    int get_max_top() {
        return greatest_depth_reached;
    }
};

int parentesis(const string& s) {
    Stack stack(s.size());
    for (char c : s) {
        if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            stack.pop();
        }
    }
    return stack.get_max_top();
}
int main() {
    cout << parentesis("(1+1)") << endl;
    cout << parentesis("(()(2+3))") << endl;
    cout << parentesis("((2-1)*((9-3)))") << endl;
    cout << parentesis("(((8+1)+2))") << endl;
    cout << parentesis("((((0*2)+1)*2))") << endl;
    cout << parentesis("((()(())()))") << endl;
    return 0;
}