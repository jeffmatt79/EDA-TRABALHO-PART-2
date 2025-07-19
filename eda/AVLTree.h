#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename K, typename V>
class AVLTree {
private:
    struct Node {
        K key;
        V value;
        Node *left, *right;
        int height;
        Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int _size;
    int comparisons;
    int rotations;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) {
        return height(n->left) - height(n->right);
    }

    void updateHeight(Node* n) {
        n->height = std::max(height(n->left), height(n->right)) + 1;
    }

    Node* rotateRight(Node* y) {
     rotations++; 
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
         rotations++; 
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
               
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
                 
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) {
            _size++;
            return new Node(key, value);
        }
        comparisons++;
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else{
        
            node->value++;
            return node; // desnecessario na aplicação, na main já fazemos a verificação se existe ou não a palavra já 
}
        return balance(node);
    }

    Node* find(Node* node, K& key) {
        if (!node) return nullptr;
        comparisons++;
        if (key == node->key) return node;
        if (key < node->key)
            return find(node->left, key);
        else
            return find(node->right, key);
    }

    void toVector(Node* node, std::vector<std::pair<K, V>>& vec) {
        if (!node) return;
        toVector(node->left, vec);
        vec.push_back({node->key, node->value});
        toVector(node->right, vec);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    void printInOrder(Node* node, std::ostream& out) {
    if (!node) return;
    printInOrder(node->left, out);
    out << node->key << " " << node->value << "\n";
    printInOrder(node->right, out);
}
 void printChar(Node* node, std::ostream& out, char initial) {
    if (!node) return;

    printChar(node->left, out, initial);

    if (!node->key.empty() && node->key[0] == initial)
        out << node->key << " " << node->value << "\n";

    printChar(node->right, out, initial);
}
 

public:
    AVLTree() : root(nullptr), _size(0), comparisons(0), rotations(0) {}

    void insert(const K& key, const V& Value) {
        root = insert(root, key, Value );
    }
    int getRotations()  {
    return rotations;
}

    void update(const K& key, const V& value) {
        Node* n = find(root, const_cast<K&>(key));
        if (n) n->value = value;
    }

    V get(const K& key) {
        Node* n = find(root, const_cast<K&>(key));
        return n ? n->value : V();
    }

    bool exists(const K& key) {
        return find(root, const_cast<K&>(key)) != nullptr;
    }

    int size() {
        return _size;
    }

    int getComparisons() {
        return comparisons;
    }
      void printInOrder(std::ostream& out) {
    printInOrder(root, out);
}

    void clear() {
        clear(root);
        root = nullptr;
        _size = 0;
        comparisons = 0;
    }
   void printChar(char initial, std::ostream& out = std::cout) {
    printChar(root, out, initial);
}
    void toVector(std::vector<std::pair<K, V>>& vec) {
        toVector(root, vec);
    }
};

