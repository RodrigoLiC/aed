#include <iostream>
#include <vector>

using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
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

    vector<string> auxSuggest(const string& prefix, TrieNode* node) {
        vector<string> result;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i;
                string newPrefix = prefix + c;
                if (node->children[i]->isEndOfWord) {
                    result.push_back(newPrefix);
                    if (result.size() > 2) {
                        return result;
                    }
                }
                vector<string> suggestions = auxSuggest(newPrefix, node->children[i]);

                for (const string& suggestion : suggestions) {
                    result.push_back(suggestion);
                    if (result.size() > 2) {
                        return result;
                    }
                }
            }
        }
        return result;
    }

    vector<string> suggest(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return {};
            }
            node = node->children[index];
        }
        vector<string> result;
        if (node->isEndOfWord) {
            result.push_back(prefix);
        }
        vector<string> suggestions = auxSuggest(prefix, node);
        for (const string& suggestion : suggestions) {
            result.push_back(suggestion);
            if (result.size() > 2) {
                return result;
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie trie;
        for (const string& product : products) {
            trie.insert(product);
        }
        string prefix = "";
        vector<vector<string>> result;
        for (char c : searchWord) {
            prefix += c;
            vector<string> suggestions = trie.suggest(prefix);
            result.push_back(suggestions);
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> products = {"mobile","mouse","moneypot","monitor","mousepad"};
    vector<vector<string>> m = s.suggestedProducts(products,"mores");

    for (const vector<string>& v : m) {
        for (const string& s : v) {
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}