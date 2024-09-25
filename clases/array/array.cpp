#include <iostream>

using namespace std;

template <typename T>
class Arr{
private:
    int size;
    T* array;
public:
    Arr(int size) {
        this->size = size;
        this->array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = T();
        }
    }
    ~Arr() {
        delete[] array;
    }
    T& operator[](int index) {
        if (index < 0) {
            return array[index];
        }
        if (index >= size) {
            int newSize = size;
            while (index >= newSize) {
                newSize *= 2;
            }
            reSize(newSize);
        }
        return array[index];
    }
    void reSize(int newSize) {
        T *newArray = new T[newSize];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        for (int i = size; i < newSize; i++) {
            newArray[i] = T();
        }
        delete[] array;
        array = newArray;
        size = newSize;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};


int main() {
    Arr<int> arr(4);


    arr[4] = 2;
    cout << arr[4] << endl;

    arr.print();
    cout << endl;
    while (true) {
        int index;
        cout << "Enter index: ";
        cin >> index;
        cout << "Enter value: ";
        cin >> arr[index];
        arr.print();
    }
    return 0;
}