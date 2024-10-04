#include <iostream>

using namespace std;

struct Voxel {
    int r, g, b;
};

struct OctreeNode {
    static const int CHILDREN_LENGTH = 8;
    OctreeNode* children[CHILDREN_LENGTH];
    bool isLeaf;
    Voxel voxelData;

    OctreeNode() : isLeaf(true) {
        for (int i = 0; i < CHILDREN_LENGTH; i++) {
            children[i] = nullptr;
        }
    }

    ~OctreeNode() {
        clear();
    }

    void insert(const Voxel &voxel, double x, double y, double z, int depth, double size) {
        if (depth == 0) {
            isLeaf = true;
            voxelData = voxel;
            return;
        }
        isLeaf = false;

        double mid = size / 2;
        int index = 0;

        if (x >= mid) {
            index += 1;
            x -= mid;
        }
        if (y >= mid) {
            index |= 2;
            y -= mid;
        }
        if (z >= mid) {
            index |= 4;
            z -= mid;
        }

        if (children[index] == nullptr) {
            children[index] = new OctreeNode();
        }

        children[index]->insert(voxel, x, y, z, depth-1, mid);
    }

    void print(double x, double y, double z, double size){
        double mid = size / 2;

        if (isLeaf) {
            cout << "Voxel en rango ";
            cout << "(" << x << ", " << y << ", " << z << ") - (" << x + size << ", " << y + size << ", " << z + size << ")";
            return;
        }

        cout << "Nodo con rango";
        cout << " (" << x << ", " << y << ", " << z << ") - (" << x + size << ", " << y + size << ", " << z + size << ")";
        cout << " { ";
        for (int i = 0; i < CHILDREN_LENGTH; i++) {
            if (children[i] != nullptr) {
                children[i]->print(x + (i & 1) * mid, y + (i & 2)/2 * mid, z + (i & 4)/4 * mid, mid);
            }
        }
        cout << " } ";
    }

    void clear() {
        for (int i = 0; i < CHILDREN_LENGTH; i++) {
            if (children[i] != nullptr) {
                children[i]->clear();
                delete children[i];
                children[i] = nullptr;
            }
        }
    }
};

class Octree {
public:
    OctreeNode root;
    int depth;
    double size;

    Octree(double size, int depth) : size(size), depth(depth) {}

    void insert(const Voxel &voxel, double x, double y, double z) {
        root.insert(voxel, x, y, z, depth, size);
    }

    void print(){
        root.print(0, 0, 0, size);
    }

    void clear() {
        root.clear();
    }
};

int main() {
    Octree oct(32, 8);
    Voxel redVoxel = {255, 0, 0};
    oct.insert(redVoxel, 10, 10, 10);
    oct.print();
    oct.clear();
    return 0;
}