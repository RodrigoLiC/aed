#include <iostream>

using namespace std;

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void auxInsert(Node* node, T value) {
        if (value < node->data) {
            if (node->left == nullptr) {
                node->left = new Node(value);
            } else {
                auxInsert(node->left, value);
            }
        } else if (value > node->data) {
            if (node->right == nullptr) {
                node->right = new Node(value);
            } else {
                auxInsert(node->right, value);
            }
        }
    }

    void auxClear(Node* node) {
        if (node != nullptr) {
            auxClear(node->left);
            auxClear(node->right);
            delete node;
        }
    }

    int auxHeight(Node* node) {
        if (node == nullptr) return -1;
        int left = auxHeight(node->left);
        int right = auxHeight(node->right);
        return 1 + max(left, right);
    }


    void preOrder(Node* node) const {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) const {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }


public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { auxClear(root); }

    void insert(T value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }
        auxInsert(root, value);
    }

    int height() {
        return auxHeight(root);
    }

    void preOrderTraversal() const {
        preOrder(root);
    }
    void inOrderTraversal() const {
        inOrder(root);
    }
    void postOrderTraversal() const {
        postOrder(root);
    }

    void drawCurrentDepth(Node* node, int depth, int spaces) {
        if (node == nullptr) {
            if (depth == 0) {
                for (int i = 0; i < spaces; i++) cout << " ";
                cout << "X";
                for (int i = 0; i < spaces + 1; i++) cout << " ";
                return;
            }
            drawCurrentDepth(nullptr, depth - 1, spaces);
            drawCurrentDepth(nullptr, depth - 1, spaces);
            return;
        }
        if (depth == 0) {
            for (int i = 0; i < spaces; i++) cout << " ";
            cout << node->data;
            for (int i = 0; i < spaces + 1; i++) cout << " ";
            return;
        }
        drawCurrentDepth(node->left, depth - 1, spaces);
        drawCurrentDepth(node->right, depth - 1, spaces);
    }

    void draw() {
        for(int i = 0; i <= height(); i++) {
            int prod = 1<<(height() - i + 1);
            drawCurrentDepth(root, i, prod-1);
            cout << "\n";
        }
    }
};

int main() {
    BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "Pre-order Traversal: ";
    tree.preOrderTraversal();
    cout << "\n";
    cout << "In-order Traversal: ";
    tree.inOrderTraversal();
    cout << "\n";
    cout << "Post-order Traversal: ";
    tree.postOrderTraversal();
    cout << "\n";

    tree.draw();

    BinaryTree<int> tree2;
    tree2.insert(1);
    tree2.insert(2);
    tree2.insert(3);
    tree2.insert(4);

    cout << "inOrderTraversal: ";
    tree2.inOrderTraversal();
    cout << "\n";
    tree2.draw();


    return 0;
}
