#ifndef BST_H
#define BST_H

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& d) : data(d), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& data) {
        if (!node) node = new Node(data);
        else if (data < node->data) insert(node->left, data);
        else insert(node->right, data);
    }

    void inorder(Node* node, void (*callback)(const T&)) const {
        if (!node) return;
        inorder(node->left, callback);
        callback(node->data);
        inorder(node->right, callback);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& data) {
        insert(root, data);
    }

    void inorder(void (*callback)(const T&)) const {
        inorder(root, callback);
    }
};

#endif
