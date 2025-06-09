// type:
// 0: sin camara (no cubierto)
// 1: cubierto por hijo
// 2: con camara (cubierto)

// aux -> pair<type, camera_count>
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        if (!root) return 0;
        pair<int, int> result = aux(root);
        return result.second + (result.first == 0 ? 1 : 0);
    }

    pair<int, int> aux(TreeNode* node) {
        //un nodo inexistente (puntero a nulo) no cubre ni necesita cobertura (type 1)
        if (!node) return {1, 0}; 

        pair<int, int> left = aux(node->left);
        pair<int, int> right = aux(node->right);

        int type = 0;
        int camera_count = left.second + right.second;
        if (left.first == 0 || right.first == 0) {
            type = 2; // colocar camara si algun hijo no esta cubierto
            camera_count++;
        } else if (left.first == 2 || right.first == 2) {
            type = 1; // cubierto por hijo
        } else {
            type = 0; // no cubierto, pero hijos cubiertos
        }
        return {type, camera_count};
    }
};
