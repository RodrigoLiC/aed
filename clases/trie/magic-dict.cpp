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
};

class MagicDictionary {
private:
    Trie trie;
public:
    MagicDictionary() {

    }

    void buildDict(vector<string> dictionary) {
        for (string word : dictionary) {
            trie.insert(word);
        }
    }

    bool search(const string& searchWord) {
        bool found = false;
        for (int i = 0; i < searchWord.size(); i++) {
            string alteredWord = searchWord;
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (j != searchWord[i] - 'a'){
                    alteredWord[i] = j + 'a';
                    found = found || trie.search(alteredWord);
                }
            }
        }

        return found;
    }
};

int main() {
    MagicDictionary magicDictionary;
    magicDictionary.buildDict({"hello", "leetcode","a"});
    cout<<magicDictionary.search("hello"); // return False
    cout<<magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
    cout<<magicDictionary.search("hell"); // return False
    cout<<magicDictionary.search("leetcoded"); // return False


    return 0;
}