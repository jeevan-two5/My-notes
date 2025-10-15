#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;
//O(klogn) , k is the number of overlapping intervals
struct Interval {
    int low, high;
    bool operator<(const Interval& other) const { return low < other.low; }
};

enum Color { RED, BLACK };
struct Node {
    Interval i;
    int max;
    Color color;
    Node *left, *right, *parent;
    static Node* NIL;

    Node(Interval interval) : i(interval), max(interval.high), color(RED) {
        left = right = parent = NIL;
    }
    Node(int is_sentinel) {
        if (is_sentinel == 0) {
            i = {INT_MIN, INT_MIN};
            max = INT_MIN;
            color = BLACK;
            left = right = parent = this;
        }
    }
};
Node* Node::NIL = new Node(0);

class IntervalTree {
private:
    Node* root;

    bool isOverlapping(Interval i1, Interval i2) {
        return i1.low <= i2.high && i2.low <= i1.high;
    }

    Node* insert_recursive(Node* x, Interval interval) {
        if (x == Node::NIL) return new Node(interval);
        if (interval.low < x->i.low) {
            x->left = insert_recursive(x->left, interval);
            x->left->parent = x;
        } else {
            x->right = insert_recursive(x->right, interval);
            x->right->parent = x;
        }
        x->max = max({x->i.high, 
                      (x->left != Node::NIL ? x->left->max : INT_MIN),
                      (x->right != Node::NIL ? x->right->max : INT_MIN)});
        return x;
    }

    // ----------- NEW: find one overlapping interval in O(log n) -----------
    Node* overlapSearch(Node* x, Interval query) {
        while (x != Node::NIL) {
            if (isOverlapping(x->i, query)) return x;
            else if (x->left != Node::NIL && x->left->max >= query.low)
                x = x->left;
            else
                x = x->right;
        }
        return Node::NIL;
    }

    // ----------- BST Delete Helper -----------
    Node* minValueNode(Node* x) {
        while (x->left != Node::NIL) x = x->left;
        return x;
    }

    Node* delete_recursive(Node* root, Interval interval) {
        if (root == Node::NIL) return Node::NIL;

        if (interval.low < root->i.low)
            root->left = delete_recursive(root->left, interval);
        else if (interval.low > root->i.low)
            root->right = delete_recursive(root->right, interval);
        else { // found the node
            if (root->left == Node::NIL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == Node::NIL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->i = temp->i;
            root->right = delete_recursive(root->right, temp->i);
        }

        // update max
        root->max = max({root->i.high,
                         (root->left != Node::NIL ? root->left->max : INT_MIN),
                         (root->right != Node::NIL ? root->right->max : INT_MIN)});
        return root;
    }

    void inorder_recursive(Node* x) {
        if (x != Node::NIL) {
            inorder_recursive(x->left);
            cout << "[" << x->i.low << ", " << x->i.high << "] (max=" << x->max << ")\n";
            inorder_recursive(x->right);
        }
    }

    void delete_tree(Node* x) {
        if (x != Node::NIL) {
            delete_tree(x->left);
            delete_tree(x->right);
            delete x;
        }
    }

public:
    IntervalTree() : root(Node::NIL) {}
    ~IntervalTree() { delete_tree(root); }

    void insert(Interval i) { root = insert_recursive(root, i); }
    void inorder() { inorder_recursive(root); }

    // NEW: delete interval
    void deleteInterval(Interval i) { root = delete_recursive(root, i); }

    // NEW: find all overlaps in O(k log n)
    vector<Interval> overlapSearchAll_klogn(Interval query) {
        vector<Interval> res;
        while (true) {
            Node* x = overlapSearch(root, query);
            if (x == Node::NIL) break;
            res.push_back(x->i);
            deleteInterval(x->i); // remove and continue
        }
        return res;
    }
};

// -------------------- DEMO --------------------
int main() {
    IntervalTree tree;

    Interval intervals[] = {
        {17, 19}, {5, 11}, {4, 8}, {15, 18}, {7,10},{22,23}
    };

    cout << "Inserting intervals...\n";
    for (auto& it : intervals)
        tree.insert(it);

    cout << "\nInorder traversal (with max values):\n";
    tree.inorder();
    cout << "\n--------------------------------------\n";

    Interval query = {21, 22};
    cout << "Query: [" << query.low << ", " << query.high << "]\n";

    vector<Interval> results = tree.overlapSearchAll_klogn(query);

    if (results.empty())
        cout << "No overlapping intervals found.\n";
    else {
        cout << "Overlapping intervals:\n";
        for (auto& r : results)
            cout << "  [" << r.low << ", " << r.high << "]\n";
    }

    return 0;
}

