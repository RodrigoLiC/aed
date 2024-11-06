#include <iostream>
#include <vector>

using namespace std;

template <typename edgeValueType>
class Grafo {
private:
    struct Pair {
        int key;
        edgeValueType value;

        Pair() : key(int()), value(edgeValueType()) {}
        Pair(const int& key, const edgeValueType& value) : key(key), value(value) {}

        void setValue(const edgeValueType& newValue) {
            value = newValue;
        }
    };

    bool isDirected;
    int numVertices;
    vector<vector<Pair>> listaAdyacencia;

public:
    Grafo(int vertices, bool dirigido = false) {
        numVertices = vertices;
        isDirected = dirigido;
        listaAdyacencia.resize(numVertices);
    }

    void agregarArista(int origen, int destino, edgeValueType value) {
        if(origen < 0 || origen >= numVertices || destino < 0 || destino >= numVertices) {
            cout << "Error: Vertices fuera de rango" << endl;
            return;
        }
        if(isDirected){ // Dirigido
            listaAdyacencia[origen].push_back(Pair(destino, value));
            return;
        } else { // No dirigido
            listaAdyacencia[origen].push_back(Pair(destino, value));
            listaAdyacencia[destino].push_back(Pair(origen, value));
        }
    }

    void imprimirGrafo() {
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertice " << i << ":";
            for (Pair arista : listaAdyacencia[i]) {
                cout << " -> " << arista.key << ":("<< arista.value << ")";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices = 5;
    Grafo<float> grafo(vertices, true);

    grafo.agregarArista(0, 1, 2.1);
    grafo.agregarArista(0, 4,3.3);
    grafo.agregarArista(1, 2,4.3);
    grafo.agregarArista(1, 3,2.2);
    grafo.agregarArista(1, 4,5.6);
    grafo.agregarArista(2, 3,2.6);
    grafo.agregarArista(3, 4,1.3);

    grafo.imprimirGrafo();

    return 0;
}
