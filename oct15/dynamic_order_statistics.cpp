#include <iostream>
#include <stdexcept>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    // CRITICAL AUGMENTATION: Stores the size of the subtree rooted at this node
    int size; 
    Node* parent;
    Node* left;
    Node* right;

    Node(int k, Color c) 
        : key(k), color(c), size(1), parent(nullptr), left(nullptr), right(nullptr) {}

    // Constructor for the NIL sentinel node
    Node() 
        : key(0), color(BLACK), size(0), parent(nullptr), left(nullptr), right(nullptr) {}
};

class OrderStatisticRBTree {
private:
    Node* Tnil;
    Node* root;

    // Helper to update the size of a node based on its children's sizes
    void updateSize(Node* x) {
        if (x != Tnil) {
            x->size = x->left->size + x->right->size + 1;
        }
    }

    // Rotations (Update size after rotation)

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != Tnil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        // ... (rest of standard RBT links update) ...
        if (x->parent == Tnil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

        // AUGMENTATION: Update sizes *in order* (x's size depends on its new children)
        updateSize(x); 
        updateSize(y); // y's size depends on x's new size
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != Tnil) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        // ... (rest of standard RBT links update) ...
        if (y->parent == Tnil) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;

        // AUGMENTATION: Update sizes *in order*
        updateSize(y);
        updateSize(x);
    }
    
    // ... (rbTransplant, rbInsertFixup, rbDeleteFixup implementations are here) ...
    // Note: All functions that modify the tree structure (insert, delete, fixups,
    // transplant) must call updateSize() on the affected nodes up the path 
    // to the root. For simplicity, only rotations are shown explicitly updating size,
    // but a full implementation would ensure size updates in all modifying functions.

    // ******************************************************
    // RB-INSERT and RB-DELETE with Size Augmentation
    // ******************************************************

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == Tnil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* treeMinimum(Node* x) {
        while (x->left != Tnil) {
            x = x->left;
        }
        return x;
    }

    void rbInsertFixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right; // uncle
                if (y->color == RED) { // Case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) { // Case 2
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else { // Symmetric cases
                Node* y = z->parent->parent->left; // uncle
                if (y->color == RED) { // Case 1 sym
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) { // Case 2 sym
                        z = z->parent;
                        rightRotate(z);
                    }
                    // Case 3 sym
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void rbDeleteFixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right; // sibling
                // Case 1, 2, 3, 4 logic... (same as before)
                if (w->color == RED) { /* Case 1 */ w->color = BLACK; x->parent->color = RED; leftRotate(x->parent); w = x->parent->right; }
                if (w->left->color == BLACK && w->right->color == BLACK) { /* Case 2 */ w->color = RED; x = x->parent; }
                else {
                    if (w->right->color == BLACK) { /* Case 3 */ w->left->color = BLACK; w->color = RED; rightRotate(w); w = x->parent->right; }
                    /* Case 4 */ w->color = x->parent->color; x->parent->color = BLACK; w->right->color = BLACK; leftRotate(x->parent); x = root; 
                }
            } else { /* Symmetric Cases */
                Node* w = x->parent->left; // sibling
                // Case 1, 2, 3, 4 symmetric logic...
                if (w->color == RED) { /* Case 1 sym */ w->color = BLACK; x->parent->color = RED; rightRotate(x->parent); w = x->parent->left; }
                if (w->right->color == BLACK && w->left->color == BLACK) { /* Case 2 sym */ w->color = RED; x = x->parent; }
                else {
                    if (w->left->color == BLACK) { /* Case 3 sym */ w->right->color = BLACK; w->color = RED; leftRotate(w); w = x->parent->left; }
                    /* Case 4 sym */ w->color = x->parent->color; x->parent->color = BLACK; w->left->color = BLACK; rightRotate(x->parent); x = root;
                }
            }
        }
        x->color = BLACK;
    }


public:
    OrderStatisticRBTree() {
        Tnil = new Node();
        Tnil->color = BLACK;
        root = Tnil;
    }

    void insert(int key) {
        Node* z = new Node(key, RED); 
        z->left = Tnil;
        z->right = Tnil;

        Node* y = Tnil;
        Node* x = root;

        // 1. Standard BST Insertion and size path update
        while (x != Tnil) {
            // AUGMENTATION: Increment size for nodes along the path
            x->size++; 
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == Tnil) {
            root = z; 
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }

        // 2. Fixup (Rotations will automatically update sizes)
        rbInsertFixup(z);
    }
    
    void deleteNode(int key) {
        Node* z = search(key);
        if (z == Tnil) return;

        Node* y = z;
        Node* x;
        Color y_original_color = y->color;

        if (z->left == Tnil) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == Tnil) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        
        // AUGMENTATION: Decrement size for nodes along the path (from x's new parent)
        for (Node* curr = x->parent; curr != Tnil; curr = curr->parent) {
            curr->size--;
        }

        delete z;

        if (y_original_color == BLACK) {
            rbDeleteFixup(x);
        }
    }

    Node* search(int key) {
        Node* current = root;
        while (current != Tnil && current->key != key) {
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return current;
    }

    // ******************************************************
    // DYNAMIC ORDER STATISTICS OPERATION: OS-SELECT
    // ******************************************************

    /**
     * Finds the node containing the element with rank i (the i-th smallest element).
     * @param i The rank (1-based index) of the element to find.
     * @return The key of the i-th smallest element.
     */
    int OS_Select(int i) {
        if (i < 1 || i > root->size) {
            throw out_of_range("Rank 'i' is out of bounds.");
        }
        return OS_Select_Helper(root, i)->key;
    }

    Node* OS_Select_Helper(Node* x, int i) {
        // r = number of nodes in the left subtree + 1 (the rank of node x itself)
        int r = x->left->size + 1;

        if (i == r) {
            return x; // Found the i-th smallest element
        } else if (i < r) {
            // The i-th smallest element is in the left subtree
            return OS_Select_Helper(x->left, i);
        } else {
            // The i-th smallest element is in the right subtree
            // We need to look for the (i - r)-th smallest element in the right subtree
            return OS_Select_Helper(x->right, i - r);
        }
    }

    // Utility for demonstration
    void inOrderTraversal() const {
        cout << "In-Order Traversal (Key/Size): ";
        inOrderHelper(root);
        cout << endl;
    }
    
    void inOrderHelper(Node* node) const {
        if (node != Tnil) {
            inOrderHelper(node->left);
            cout << node->key << "/" << node->size << " ";
            inOrderHelper(node->right);
        }
    }
};

int main() {
    OrderStatisticRBTree os_rbt;

    // Insert elements: {15, 6, 18, 3, 7, 17, 20}
    int keys[] = {77, 67, 65, 70, 68,72,80,78, 81};
    for (int key : keys) {
        os_rbt.insert(key);
    }

    cout << "--- Initial Order-Statistic Red-Black Tree ---" << endl;
    os_rbt.inOrderTraversal(); // Output will show keys and their subtree sizes
    cout << "Total elements: " << os_rbt.search(15)->size << endl; // Root's size

    // Testing OS_Select (Find the i-th smallest element)
    cout << "\n--- OS-SELECT Testing ---" << endl;

    // The keys in sorted order are: 3, 6, 7, 15, 17, 18, 20
    
    try {
        int rank1 = 1; // Expected: 3
        cout << "The " << rank1 << "-st smallest element is: " << os_rbt.OS_Select(rank1) << endl;

        int rank4 = 4; // Expected: 15
        cout << "The " << rank4 << "-th smallest element is: " << os_rbt.OS_Select(rank4) << endl;

        int rank7 = 7; // Expected: 20
        cout << "The " << rank7 << "-th smallest element is: " << os_rbt.OS_Select(rank7) << endl;

    } catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
