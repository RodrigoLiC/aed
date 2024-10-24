#include <iostream>
#include <vector>
using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int maxCount;
    int count;

    TrieNode() {
        isEndOfWord = false;
        maxCount = 0;
        count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
        node->count++;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }

    void updateMaxCount(TrieNode* node) {
        if (node == nullptr) {return;}
        node->maxCount = node->count;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                if (node->children[i]->maxCount > node->maxCount)
                node->maxCount = max(node->maxCount, node->children[i]->maxCount);
            }
        }
    }

    void auxUpdateAll(TrieNode* node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                auxUpdateAll(node->children[i]);
            }
        }
        updateMaxCount(node);
    }

    void updateAll() {
        auxUpdateAll(root);
    }

    string popMax() {
        TrieNode* node = root;
        string result = "";
        updateAll();
        while (true) {
            int maxIndex = -1;
            int maxCount = -1;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i] != nullptr) {
                    if (node->children[i]->maxCount > maxCount) {
                        maxIndex = i;
                        maxCount = node->children[i]->maxCount;
                    }
                }
            }
            if (maxIndex == -1) {
                break;
            }
            if (node->children[maxIndex]->maxCount <= node->count) {
                break;
            }
            result += (char)('a' + maxIndex);
            node = node->children[maxIndex];
        }
        node->isEndOfWord = false;
        node->count = 0;
        return result;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        Trie trie;
        for (string word : words) {
            trie.insert(word);
        }
        vector<string> result;
        for (int i = 0; i < k; i++) {
            result.push_back(trie.popMax());
        }
        return result;
    }
};

int main() {
    Solution solution;
    vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"};
    int k = 2;
    vector<string> result = solution.topKFrequent(words, k);
    for (string word : result) {
        cout << word << " ";
    }

    words = {"the","day","is","sunny","the","the","the","sunny","is","is"};
    k = 4;
    result = solution.topKFrequent(words, k);
    for (string word : result) {
        cout << word << " ";
    }

    return 0;
}