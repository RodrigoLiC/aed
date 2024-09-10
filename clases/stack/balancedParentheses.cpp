#include <iostream>

using namespace std;

class Stack {
private:
    char* arr;
    int MAX_SIZE;
    int top;
public:
    Stack(int size) : MAX_SIZE(size), top(-1) {
        arr = new char[MAX_SIZE];
    }
    ~Stack() {
        delete[] arr;
    }
    bool isEmpty() const {
        return top == -1;
    }
    void push(char c) {
        arr[++top] = c;
    }
    char pop() {
        return arr[top--];
    }
};

bool isValidParentheses(const string& s) {
    Stack stack(s.size());
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else {
            if (stack.isEmpty()) {
                return false;
            }
            char top = stack.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}

int main() {
    cout << isValidParentheses("()") << endl;  // 1
    cout << isValidParentheses("()[]{}") << endl;  // 1
    cout << isValidParentheses("{[]}") << endl;  // 1
    cout << isValidParentheses("(]") << endl;  // 0
    cout << isValidParentheses("([)]") << endl;  // 0
    cout << isValidParentheses("]") << endl;  // 0
    cout << isValidParentheses("") << endl;  // 1

    return 0;
}
