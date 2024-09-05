#ifndef BST_H
#define BST_H

#include <iostream>
#include <stdexcept> // Added for std::logic_error
#include "Date.h" // Added for Date class

template <class T>
class Bst {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Private helper functions for recursive operations
    void insertRecursive(Node*& node, const T& value);
    void inOrderTraversalRecursive(Node* node) const;
    void preOrderTraversalRecursive(Node* node) const;
    void postOrderTraversalRecursive(Node* node) const;
    bool searchRecursive(Node* node, const T& value) const;
    void removeRecursive(Node*& node, const T& value);
    void deleteTreeRecursive(Node*& node);
    void copyRecursive(Node*& currentNode, const Node* otherNode); // Added function for deep copy

    // Added declaration of findMin function
    Node* findMin(Node* node) const;

public:
    // Constructors and destructor
    Bst();
    Bst(const Bst& other); // Copy constructor
    Bst& operator=(const Bst& other); // Assignment operator
    ~Bst();

    // Public member functions
    void insert(const T& value);
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    bool search(const T& value) const;
    void remove(const T& value);
    void deleteTree();
};

#include "Bst.cpp"

// Implementation of the copy constructor
template <class T>
Bst<T>::Bst(const Bst& other) : root(nullptr) {
    // Call the recursive function to perform deep copy
    insertRecursive(this->root, other.root->data);
    copyRecursive(this->root, other.root);
}

// Recursive function for deep copy
template <class T>
void Bst<T>::copyRecursive(Node*& currentNode, const Node* otherNode) {
    if (otherNode != nullptr) {
        insertRecursive(currentNode, otherNode->data);
        copyRecursive(currentNode->left, otherNode->left);
        copyRecursive(currentNode->right, otherNode->right);
    }
}

// Implementation of the assignment operator
template <class T>
Bst<T>& Bst<T>::operator=(const Bst& other) {
    if (this != &other) {
        // Delete the existing tree
        deleteTreeRecursive(this->root);

        // Perform deep copy
        insertRecursive(this->root, other.root->data);
        copyRecursive(this->root, other.root);
    }
    return *this;
}

// Recursive insert operation
template <class T>
void Bst<T>::insertRecursive(Node*& node, const T& value) {
    if (node == nullptr) {
        node = new Node(value);
    } else {
        if (value < node->data) {
            insertRecursive(node->left, value);
        } else {
            insertRecursive(node->right, value);
        }
    }
}

// Recursive in-order traversal
template <class T>
void Bst<T>::inOrderTraversalRecursive(Node* node) const {
    if (node != nullptr) {
        inOrderTraversalRecursive(node->left);
        std::cout << node->data << " ";
        inOrderTraversalRecursive(node->right);
    }
}

// Recursive pre-order traversal
template <class T>
void Bst<T>::preOrderTraversalRecursive(Node* node) const {
    if (node != nullptr) {
        std::cout << node->data << " ";
        preOrderTraversalRecursive(node->left);
        preOrderTraversalRecursive(node->right);
    }
}

// Recursive post-order traversal
template <class T>
void Bst<T>::postOrderTraversalRecursive(Node* node) const {
    if (node != nullptr) {
        postOrderTraversalRecursive(node->left);
        postOrderTraversalRecursive(node->right);
        std::cout << node->data << " ";
    }
}

// Recursive search operation
template <class T>
bool Bst<T>::searchRecursive(Node* node, const T& value) const {
    if (node == nullptr) {
        return false;
    }

    if (value == node->data) {
        return true;
    } else if (value < node->data) {
        return searchRecursive(node->left, value);
    } else {
        return searchRecursive(node->right, value);
    }

    // Added a return statement or an exception at the end of the function
    // return false;
    throw std::logic_error("Invalid state in searchRecursive function");
}

// Recursive remove operation
template <class T>
void Bst<T>::removeRecursive(Node*& node, const T& value) {
    if (node == nullptr) {
        return;
    }

    if (value < node->data) {
        removeRecursive(node->left, value);
    } else if (value > node->data) {
        removeRecursive(node->right, value);
    } else {
        if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* temp = findMin(node->right);
            node->data = temp->data;
            removeRecursive(node->right, temp->data);
        }
    }
}

// Recursive delete tree operation
template <class T>
void Bst<T>::deleteTreeRecursive(Node*& node) {
    if (node != nullptr) {
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);
        delete node;
        node = nullptr;
    }
}

// Constructors and destructor
template <class T>
Bst<T>::Bst() : root(nullptr) {}

template <class T>
Bst<T>::~Bst() {
    // Implementation...
}

// Public member functions
template <class T>
void Bst<T>::insert(const T& value) {
    insertRecursive(root, value);
}

// Perform in-order traversal of the binary search tree
template <class T>
void Bst<T>::inOrderTraversal() const {
    inOrderTraversalRecursive(root);
    std::cout << std::endl;
}

// Perform pre-order traversal of the binary search tree
template <class T>
void Bst<T>::preOrderTraversal() const {
    preOrderTraversalRecursive(root);
    std::cout << std::endl;
}

// Perform post-order traversal of the binary search tree
template <class T>
void Bst<T>::postOrderTraversal() const {
    postOrderTraversalRecursive(root);
    std::cout << std::endl;
}

// Search for a value in the binary search tree
template <class T>
bool Bst<T>::search(const T& value) const {
    return searchRecursive(root, value);
}

// Remove a value from the binary search tree
template <class T>
void Bst<T>::remove(const T& value) {
    removeRecursive(root, value);
}

// Delete the entire binary search tree
template <class T>
void Bst<T>::deleteTree() {
    deleteTreeRecursive(root);
}
template <class T>
typename Bst<T>::Node* Bst<T>::findMin(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    } else if (node->left == nullptr) {
        return node;
    } else {
        return findMin(node->left);
    }
}

#endif // BST_H
