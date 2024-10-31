#include <iostream>

using namespace std;

class BPTreeNode {
public:
    int *keys;             // Arreglo dinámico para almacenar claves
    BPTreeNode **children; // Arreglo de punteros a hijos
    int keyCount;          // Número actual de claves en el nodo
    int M;                 // Grado del nodo (máximo de hijos)

    bool isLeaf;           // Indica si el nodo es una hoja
    BPTreeNode *nextLeaf;  // Puntero al siguiente nodo hoja (si es hoja)

    // Constructor del nodo que recibe si es hoja y el grado M
    BPTreeNode(bool isLeaf, int M);

    // Liberar memoria
    ~BPTreeNode();
};

BPTreeNode::BPTreeNode(bool isLeaf, int M) : isLeaf(isLeaf), keyCount(0), nextLeaf(nullptr), M(M) {
    keys = new int[M - 1];
    children = new BPTreeNode*[M];
    for (int i = 0; i < M; i++) {
        children[i] = nullptr;
    }
}

BPTreeNode::~BPTreeNode() {
    delete[] keys;
    delete[] children;
}

class BPTree {
public:
    BPTreeNode *root;
    int M;

    BPTree(int M) : root(nullptr), M(M) {}
    void insert(int key);
    BPTreeNode* search(int key);
    void remove(int key);
    ~BPTree() {delete root;}

private:
    // Función recursiva para insertar una clave en un nodo específico
    void insertNonFull(BPTreeNode *node, int key);

    // Función para dividir un nodo lleno
    void splitChild(BPTreeNode *parent, int index, BPTreeNode *child);

    // Función para buscar una clave en un nodo específico
    BPTreeNode* auxSearch(BPTreeNode* node, int key);

    // Función recursiva para eliminar una clave desde un nodo específico
    void removeFromNode(BPTreeNode *node, int key);

    // Función para obtener el predecesor de una clave en un nodo interno
    int findPrev(BPTreeNode *node, int index);

    // Función para manejar la redistribución o fusión en caso de déficit
    void deficit(BPTreeNode *node, int index);
};

BPTreeNode* BPTree::search(int key) {
    return auxSearch(root, key);
}

BPTreeNode* BPTree::auxSearch(BPTreeNode* node, int key) {
    if (node == nullptr) {return nullptr;}
    int i = 0;

    // Encontrar la posición de la clave en el nodo
    while (i < node->keyCount && key > node->keys[i]) {i++;}

    // Retornar el nodo si se encontró
    if (i < node->keyCount && node->keys[i] == key) {
        return node;
    }

    // Si se llega a una hoja y no se encontró
    if (node->isLeaf) {
        return nullptr;
    }

    // Si ninguno se cumple seguir buscando
    return auxSearch(node->children[i], key);
}

void BPTree::insert(int key) {
    if (!root) { // raiz nula
        root = new BPTreeNode(true, M);
        root->keys[0] = key;
        root->keyCount = 1;
    } else { // raiz llena
        if (root->keyCount == M - 1) {
            // Crear un nuevo nodo que se convertirá en la nueva raíz
            BPTreeNode *newRoot = new BPTreeNode(false, M);
            newRoot->children[0] = root;

            // Divide la raíz y mueve la clave media al nuevo nodo raíz
            splitChild(newRoot, 0, root);

            // Insertar la clave en el nodo adecuado
            int i = (newRoot->keys[0] < key) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);

            // Actualizar la raíz
            root = newRoot;
        } else { // raiz no llena
            insertNonFull(root, key);
        }
    }
}

void BPTree::insertNonFull(BPTreeNode *node, int key) {
    int i = node->keyCount - 1;

    if (node->isLeaf) {
        // mover claves mayores mientras se busca la posicion
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        // Inserta la nueva clave
        node->keys[i + 1] = key;
        node->keyCount++;
    } else {
        // Encuentra el hijo adecuado para insertar la clave
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;

        // Si el hijo está lleno, lo dividimos primero
        if (node->children[i]->keyCount == M - 1) {
            splitChild(node, i, node->children[i]);

            // Reajustar en que hijo insertar la clave
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void BPTree::splitChild(BPTreeNode *parent, int index, BPTreeNode *child) {
    BPTreeNode *newNode = new BPTreeNode(child->isLeaf, M);
    int mitad = (M - 1) / 2;
    newNode->keyCount = mitad;

    for (int j = 0; j < mitad; j++) {
        newNode->keys[j] = child->keys[j + (M + 1) / 2];
    }

    if (!child->isLeaf) {
        for (int j = 0; j < (M + 1) / 2; j++) {
            newNode->children[j] = child->children[j + (M + 1) / 2];
        }
    } else {
        // Reajustar los punteros a hojas siguientes
        newNode->nextLeaf = child->nextLeaf;
        child->nextLeaf = newNode;
    }

    // Reducimos el número de claves en el hijo original
    child->keyCount = mitad;

    // Ajusta el padre para que apunte a newNode
    for (int j = parent->keyCount; j >= index + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = newNode;

    // Mueve la clave media al nodo padre
    for (int j = parent->keyCount - 1; j >= index; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[index] = child->keys[mitad];
    parent->keyCount++;
}

void BPTree::remove(int key) {
    if (!root) {return;}

    // funcion recursiva
    removeFromNode(root, key);

    // si la raiz queda vacia
    if (root->keyCount == 0) {
        BPTreeNode *temp = root;
        if (!root->isLeaf) { // si tiene hijo, este se vuelve raiz
            root = root->children[0];
        } else {
            root = nullptr;
        }
        delete temp;
    }
}

void BPTree::removeFromNode(BPTreeNode *node, int key) {
    int index = 0;

    while (index < node->keyCount && node->keys[index] < key) {
        index++;
    }

    if (index < node->keyCount && node->keys[index] == key) {
        if (node->isLeaf) { // Caso 0: El nodo es una hoja
            // Elimina la clave de la hoja
            for (int i = index; i < node->keyCount - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            node->keyCount--;
        } else {
            int pred = findPrev(node, index);
            node->keys[index] = pred;
            removeFromNode(node->children[index], pred);
        }
    } else { // La clave no está en este nodo, buscamos en el hijo adecuado
        if (node->isLeaf) {return;}

        // Determina si el hijo que contiene la clave está en déficit
        bool deficiency = (node->children[index]->keyCount < (M - 1) / 2 + 1);

        // Llama recursivamente para eliminar la clave del hijo
        removeFromNode(node->children[index], key);

        // Si el hijo tiene un déficit de claves después de la eliminación
        if (deficiency) {
            deficit(node, index);
        }
    }
}

int BPTree::findPrev(BPTreeNode *node, int index) {
    BPTreeNode *current = node->children[index];
    while (!current->isLeaf) {
        current = current->children[current->keyCount];
    }
    return current->keys[current->keyCount - 1];
}

void BPTree::deficit(BPTreeNode *node, int index) {
    BPTreeNode *child = node->children[index];
    BPTreeNode *sibling = nullptr;
    // Verificar si el hermano izquierdo puede redistribuir
    if (index != 0 && node->children[index - 1]->keyCount > (M - 1) / 2) {
        sibling = node->children[index - 1];
        for (int i = child->keyCount - 1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }
        child->keys[0] = node->keys[index - 1];
        node->keys[index - 1] = sibling->keys[sibling->keyCount - 1];
        child->keyCount++;
        sibling->keyCount--;
    }// Verificar si el hermano derecho puede redistribuir
    else if (index != node->keyCount && node->children[index + 1]->keyCount > (M - 1) / 2) {
        sibling = node->children[index + 1];
        child->keys[child->keyCount] = node->keys[index];
        node->keys[index] = sibling->keys[0];
        for (int i = 0; i < sibling->keyCount - 1; i++) {
            sibling->keys[i] = sibling->keys[i + 1];
        }

        child->keyCount++;
        sibling->keyCount--;
    } else {// Si no se puede redistribuir, se fusionan nodos
        if (index != node->keyCount) {
            sibling = node->children[index + 1];
            child->keys[child->keyCount] = node->keys[index];

            for (int i = 0; i < sibling->keyCount; i++) {
                child->keys[child->keyCount + 1 + i] = sibling->keys[i];
            }
            if (!child->isLeaf) {
                for (int i = 0; i <= sibling->keyCount; i++) {
                    child->children[child->keyCount + 1 + i] = sibling->children[i];
                }
            }
            child->keyCount += sibling->keyCount + 1;

            for (int i = index; i < node->keyCount - 1; i++) {
                node->keys[i] = node->keys[i + 1];
                node->children[i + 1] = node->children[i + 2];
            }
            node->keyCount--;
            delete sibling;
        }
    }
}


int main() {
    int M = 4; // Grado del árbol, cada nodo puede tener hasta M hijos
    BPTree tree(M);

    // Ejemplo de inserciones y búsqueda
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);
    tree.insert(80);

    BPTreeNode* result = nullptr;

    result = tree.search(20);
    if(result) {cout << "encontrado\n";} else {cout << "no encontrado\n";}

    result = tree.search(50);
    if(result) {cout << "encontrado\n";} else {cout << "no encontrado\n";}

    result = tree.search(30);
    if(result) {cout << "encontrado\n";} else {cout << "no encontrado\n";}

    tree.remove(20);
    result = tree.search(20);
    if(result) {cout << "encontrado\n";} else {cout << "no encontrado\n";}


    return 0;
}