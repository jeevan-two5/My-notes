/* problem Statement: Given a Binary Search Tree and a ‘key’ value which represents the data data of a node in this tree.
  Return the inorder predecessor and successor of the given node in the BST.

The predecessor of a node in BST is that node that will be visited just before the given node in the inorder traversal of the tree. 
Return nullptr if the given node is the one that is visited first in the inorder traversal.
The successor of a node in BST is that node that will be visited immediately after the given node in the inorder traversal of the tree. 
  Return nullptr if the given node is visited last in the inorder traversal.

  Example 1:
Input: Binary Search Tree: 5 3 7 2 4 6 9 1 -1 -1 -1 -1 -1 8 10, Key = 8
Output: Inorder Predecessor: 7, Inorder Successor: 9

*/



//          --------------------------------B R U T E --------------------------------

#include <bits/stdc++.h>
using namespace std;

// define tree node structure
struct TreeNode {
    // value of the node
    int val;
    // pointer to the left child
    TreeNode* left;
    // pointer to the right child
    TreeNode* right;
    // constructor
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// solution class
class Solution {
public:
    // find inorder successor by building inorder list and binary searching
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // container for inorder traversal
        vector<int> inorder;
        // fill inorder list
        inorderTraversal(root, inorder);
        // locate index of p->val (or insertion index)
        int idx = binarySearch(inorder, p->val);
        // handle edge cases: last element or invalid
        if (idx == (int)inorder.size() - 1 || idx == -1) {
            return nullptr;
        }
        // return a new node with successor value (mirroring given logic)
        return new TreeNode(inorder[idx + 1]);
    }

    // inorder traversal helper
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        // base case
        if (root == nullptr) return;
        // traverse left
        inorderTraversal(root->left, inorder);
        // visit node
        inorder.push_back(root->val);
        // traverse right
        inorderTraversal(root->right, inorder);
    }

    // binary search helper
    int binarySearch(vector<int>& arr, int target) {
        // search bounds
        int left = 0, right = (int)arr.size() - 1;
        // standard binary search
        while (left <= right) {
            // midpoint
            int mid = left + (right - left) / 2;
            // found case
            if (arr[mid] == target) return mid;
            // move right
            else if (arr[mid] < target) left = mid + 1;
            // move left
            else right = mid - 1;
        }
        // not found: return insertion index or -1 if at end
        return left == (int)arr.size() ? -1 : left;
    }
};


//  ------------------------------------------ B E T T E R --------------------------------------------

#include <bits/stdc++.h>
using namespace std;

// define tree node structure
struct TreeNode {
    // value of the node
    int val;
    // pointer to the left child
    TreeNode* left;
    // pointer to the right child
    TreeNode* right;
    // constructor
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// solution class
class Solution {
public:
    // find inorder successor in BST by tracking candidate
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // initialize successor pointer
        TreeNode* successor = nullptr;
        // traverse until null
        while (root != nullptr) {
            // move left while updating successor when root > p
            if (root->val > p->val) {
                successor = root;
                root = root->left;
            }
            // otherwise move right
            else {
                root = root->right;
            }
        }
        // return final successor (or null)
        return successor;
    }
};

//          ---------------------------------------- O P T I M A L ---------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

// define tree node structure
struct TreeNode {
    // value of the node
    int val;
    // pointer to left child
    TreeNode* left;
    // pointer to right child
    TreeNode* right;
    // constructor
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// solution class
class Solution {
public:
    // find inorder successor iteratively
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // initialize successor
        TreeNode* successor = nullptr;
        // traverse until root becomes null
        while (root != nullptr) {
            // when p is greater or equal, move right
            if (p->val >= root->val) {
                root = root->right;
            }
            // otherwise update successor and move left
            else {
                successor = root;
                root = root->left;
            }
        }
        // return successor (may be null)
        return successor;
    }
};

// inorder print helper
void printInOrder(TreeNode* root) {
    // base case
    if (root == nullptr) return;
    // traverse left
    printInOrder(root->left);
    // print node
    cout << root->val << " ";
    // traverse right
    printInOrder(root->right);
}


