#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

// 1. Every node is either red or black.
enum Kolor
{
    RED,
    BLACK
};

// Node structure
struct Node
{
    int key;
    Kolor color;
    Node *parent;
    Node *left;
    Node *right;

    // Constructor for the actual nodes
    Node(int k, Kolor c) : key(k), color(c), parent(nullptr), left(nullptr), right(nullptr) {}

    // Constructor for the NIL sentinel node
    Node() : key(0), color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RedBlackTree
{
private:
    // Tnil (or NIL in CLRS) is a single, black sentinel node
    // 2. The root and leaves (NIL's) are black.
    Node *Tnil;
    Node *root;

    // Helper function to replace a subtree u with subtree v
    void rbTransplant(Node *u, Node *v)
    {
        if (u->parent == Tnil)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // Rotations (used in fixup operations)

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != Tnil)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == Tnil)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != Tnil)
        {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == Tnil)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    // Insertion Fixup (based on RB-INSERT-FIXUP pseudocode) [cite: 49, 50, 51]
    void rbInsertFixup(Node *z)
    {
        // while z's parent is RED (violating property 4: If a node is red, then its parent is black)
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *y = z->parent->parent->right; // y = uncle

                if (y->color == RED)
                { // Case 1: Uncle is red [cite: 50]
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    { // Case 2: Uncle is black, z is a right child (triangular case) [cite: 51]
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: Uncle is black, z is a left child (linear case) [cite: 52]
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                // Same as above, but with 'left' and 'right' swapped (Symmetric cases)
                Node *y = z->parent->parent->left; // y = uncle

                if (y->color == RED)
                { // Case 1 symmetric
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    { // Case 2 symmetric
                        z = z->parent;
                        rightRotate(z);
                    }
                    // Case 3 symmetric
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        // 3. The root and leaves (NIL's) are black.
        root->color = BLACK;
    }

    // Deletion Fixup (To restore black-height property)
    void rbDeleteFixup(Node *x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node *w = x->parent->right; // w is the sibling

                if (w->color == RED)
                { // Case 1: Sibling is red
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK && w->right->color == BLACK)
                { // Case 2: Sibling is black, both children are black
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    { // Case 3: Sibling is black, left child is red, right child is black
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // Case 4: Sibling is black, right child is red
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root; // Terminate
                }
            }
            else
            {
                // Symmetric cases for when x is a right child
                Node *w = x->parent->left;

                if (w->color == RED)
                { // Case 1 symmetric
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK)
                { // Case 2 symmetric
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    { // Case 3 symmetric
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    // Case 4 symmetric
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root; // Terminate
                }
            }
        }
        x->color = BLACK;
    }

    Node *treeMinimum(Node *x)
    {
        while (x->left != Tnil)
        {
            x = x->left;
        }
        return x;
    }

    void inOrderHelper(Node *node) const
    {
        if (node != Tnil)
        {
            inOrderHelper(node->left);
            cout << node->key << (node->color == RED ? " (R) " : " (B) ");
            inOrderHelper(node->right);
        }
    }

public:
    RedBlackTree()
    {
        // Initialize the sentinel Tnil node (black color, default key)
        Tnil = new Node();
        Tnil->color = BLACK;
        root = Tnil;
    }

    // 1. It is a BST (Binary Search Tree)
    void insert(int key)
    {
        Node *z = new Node(key, RED); // Kolor x red [cite: 45]
        z->left = Tnil;
        z->right = Tnil;

        Node *y = Tnil;
        Node *x = root;

        // Perform standard BST insertion
        while (x != Tnil)
        {
            y = x;
            if (z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == Tnil)
        {
            root = z; // Tree was empty
        }
        else if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        // Fix up the tree properties, since RB property 3 (parent of red node is black)
        // may be violated [cite: 46]
        rbInsertFixup(z);
    }

    void deleteNode(int key)
    {
        Node *z = search(key);
        if (z == Tnil)
        {
            cout << "Key not found for deletion." << endl;
            return;
        }

        Node *y = z;
        Node *x;
        Kolor y_original_color = y->color;

        if (z->left == Tnil)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == Tnil)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;

        if (y_original_color == BLACK)
        {
            rbDeleteFixup(x);
        }
    }

    Node *search(int key)
    {
        Node *current = root;
        while (current != Tnil && current->key != key)
        {
            if (key < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return current;
    }

    void inOrderTraversal() const
    {
        cout << "In-Order Traversal (Key: (Kolor)): ";
        inOrderHelper(root);
        cout << endl;
    }
};

int main()
{
    RedBlackTree rbt;

    // 1. Initial Insertion (The original set of nodes)
    cout << "--- 1. Initial Insertion ---" << endl;
    int keys_to_insert[] = {10, 18, 7, 15, 16, 30, 25, 40, 60};
    for (int key : keys_to_insert)
    {
        rbt.insert(key);
    }
    cout << "Tree before Deletions: ";
    rbt.inOrderTraversal();
    // Example: (10 B) is the root, 7 (R) and 18 (R) are its children, etc.

    // 2. Deletion Sequence (As performed previously)
    cout << "\n--- 2. Deletion Sequence ---" << endl;
    rbt.deleteNode(18);
    cout << "Deleted 18: ";
    rbt.inOrderTraversal(); // Tree state after deleting 18

    rbt.deleteNode(7);
    cout << "Deleted 7: ";
    rbt.inOrderTraversal(); // Tree state after deleting 7

    rbt.deleteNode(10);
    cout << "Deleted 10: ";
    rbt.inOrderTraversal(); // Tree state after deleting 10

    // 3. New Insertion
    int new_key = 12;
    cout << "\n--- 3. Inserting New Node (" << new_key << ") ---" << endl;
    rbt.insert(new_key);

    cout << "\nFinal Tree after inserting " << new_key << ":" << endl;
    rbt.inOrderTraversal();

    return 0;
}