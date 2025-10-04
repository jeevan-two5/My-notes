/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.
Example 2:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2*/


//              ====================================== S O L U T I O N =====================================

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL) return NULL;
        int curr = root->val;
        if( curr < p->val && curr < q->val ) return lowestCommonAncestor(root->right, p, q);
        if( curr > p->val && curr > q->val ) return lowestCommonAncestor(root->left, p, q);

        return root;
        
    }
};




//  ------------------------------- D A A  L A B ------------------------
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to insert a new value into the BST
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

// Function to find the Lowest Common Ancestor in a BST
Node* LCA(Node* root, Node* p, Node* q) {
    if (!root) return NULL;

    if (root->data < p->data && root->data < q->data)
        return LCA(root->right, p, q);

    if (root->data > p->data && root->data > q->data)
        return LCA(root->left, p, q);

    // If one value lies on the left and one on the right, root is LCA
    return root;
}

// Function to search and return a pointer to a node with a given value
Node* find(Node* root, int val) {
    if (!root) return NULL;
    if (root->data == val) return root;
    if (val < root->data) return find(root->left, val);
    return find(root->right, val);
}

int main() {
    Node* root = NULL;
    vector<int> values = {6, 2, 9, 12, 13, 1, 0, 5};

    // Build BST
    for (int val : values)
        root = insert(root, val);

    // Choose two nodes to find LCA of (for example: 1 and 9)
    Node* p = find(root, 1);
    Node* q = find(root, 9);

    Node* lca = LCA(root, p, q);

    if (lca)
        cout << "Lowest Common Ancestor of " << p->data << " and " << q->data << " is: " << lca->data << endl;
    else
        cout << "Nodes not found in the tree." << endl;

    return 0;
}

