class Heap {
private:
    int* heap;
    int heapSize;
    int capacity;
    bool isMaxHeap;

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int extremeIndex = index;

        if (isMaxHeap) {
            if (leftChild < heapSize && heap[leftChild] > heap[extremeIndex]) {
                extremeIndex = leftChild;
            }
            if (rightChild < heapSize && heap[rightChild] > heap[extremeIndex]) {
                extremeIndex = rightChild;
            }
        } else {
            if (leftChild < heapSize && heap[leftChild] < heap[extremeIndex]) {
                extremeIndex = leftChild;
            }
            if (rightChild < heapSize && heap[rightChild] < heap[extremeIndex]) {
                extremeIndex = rightChild;
            }
        }

        if (extremeIndex != index) {
            int temp = heap[index];
            heap[index] = heap[extremeIndex];
            heap[extremeIndex] = temp;
            heapifyDown(extremeIndex);
        }
    }

    void heapifyUp(int index) {
        int parentIndex = (index - 1) / 2;
        if (parentIndex >= 0) {
            if ((isMaxHeap && heap[index] > heap[parentIndex]) ||
                (!isMaxHeap && heap[index] < heap[parentIndex])) {
                int temp = heap[index];
                heap[index] = heap[parentIndex];
                heap[parentIndex] = temp;
                heapifyUp(parentIndex);
            }
        }
    }

public:
    Heap(int cap, bool maxHeap = true) : heapSize(0), capacity(cap), isMaxHeap(maxHeap) {
        heap = new int[capacity];
    }

    ~Heap() {
        delete[] heap;
    }

    void insert(int value) {
        if (heapSize >= capacity) {
            throw runtime_error("Heap is full");
        }
        heap[heapSize] = value;
        heapifyUp(heapSize);
        heapSize++;
    }

    int extractRoot() {
        if (heapSize == 0) {
            return 0;
        }
        int rootValue = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        heapifyDown(0);
        return rootValue;
    }

    int getRoot() {
        if (heapSize == 0) {
            return 0;
        }
        return heap[0];
    }

    void printHeap() {
        for (int i = 0; i < heapSize; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

};

class Solution {
public:
    int maximumScore(int a, int b, int c) {
        Heap heap(3, true);
        heap.insert(a);
        heap.insert(b);
        heap.insert(c);
        int score = 0;
        bool valid = true;
        while (valid) {
            int x = heap.extractRoot();
            int y = heap.extractRoot();
            valid = x > 0 && y > 0;
            if (valid) {
                score++;
                heap.insert(--x);
                heap.insert(--y);
            }
        }
        return score;
    }
};