class Solution {
private:
    unordered_map<int, TreeNode*> rootsMap;
    unordered_map<int, TreeNode*> leavesMap;
    vector<int> roots;
    vector<int> leaves;
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        for (TreeNode* tree : trees) {
            rootsMap[tree->val] = tree;
            roots.push_back(tree->val);
            if (tree->left) {
                leavesMap[tree->left->val] = tree;
                leaves.push_back(tree->left->val);
            }
            if (tree->right) {
                leavesMap[tree->right->val] = tree;
                leaves.push_back(tree->right->val);
            }
        }

        TreeNode* rootNode = nullptr;
        for (int root : roots) {
            if (leavesMap.find(root) == leavesMap.end()) {
                if (rootNode) {return nullptr;} // multiple roots
                rootNode = rootsMap[root];
            }
        }
        if (!rootNode) return nullptr;
        rootNode->left = join(rootNode->left);
        rootNode->right = join(rootNode->right);
        
        if(isBST(rootNode, INT_MIN, INT_MAX)&& rootsMap.size() == 1) {
            return rootNode;
        }
        return nullptr;
    }

    TreeNode* join(TreeNode* node) {
        if (!node) return nullptr;
        if (!node->left && !node->right) {
            if (rootsMap.find(node->val) != rootsMap.end()) {
                node = rootsMap[node->val];
                rootsMap.erase(node->val);
            }
        }
        node->left = join(node->left);
        node->right = join(node->right);

        return node;
    }
    
    bool isBST(TreeNode* node, int left, int right) {
        if (!node) return true;
        if (node->val <= left || node->val >= right) return false;
        return isBST(node->left, left, node->val) && isBST(node->right, node->val, right);
    }
};
