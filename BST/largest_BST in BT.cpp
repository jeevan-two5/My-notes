/*
You're given a binary tree. Your task is to find the size of the largest subtree within this binary tree that also satisfies the properties of a Binary Search Tree (BST). The size of a subtree is defined as the number of nodes it contains.

Note: A subtree of the binary tree is considered a BST if for every node in that subtree, the left child is less than the node, and the right child is greater than the node, without any duplicate values in the subtree.

Examples :

Input: root = [5, 2, 4, 1, 3]
Root-to-leaf-path-sum-equal-to-a-given-number-copy
Output: 3
Explanation:The following sub-tree is a BST of size 3
Balance-a-Binary-Search-Tree-3-copy
Input: root = [6, 7, 3, N, 2, 2, 4]

Output: 3
Explanation: The following sub-tree is a BST of size 3:
*/

// TC :O(N)          SC:O(1)
 // Question from gfg this was..!!
#include <bits/stdc++.h>
/* Tree node structure  used in the program

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

class Nodevalue {
    public:
      int maxNode,minNode,maxsize;
      Nodevalue(int minNode,int maxNode,int maxsize){
          this-> maxNode = maxNode;
          this-> minNode = minNode;
          this-> maxsize = maxsize;
      }
};


class Solution {
  private:
     Nodevalue largeBSThelper(Node*root){
         if(!root) { return Nodevalue(INT_MAX,INT_MIN,0);
     }
     auto left = largeBSThelper(root->left);
     auto right = largeBSThelper(root->right);
     if(left.maxNode <root->data && root->data < right.minNode)
     {
         return Nodevalue(min(root->data,left.minNode),max(root->data,right.maxNode),left.maxsize + right.maxsize + 1);
         
     }
     return Nodevalue(INT_MIN,INT_MAX,max(left.maxsize,right.maxsize));
     }
    
  public:
    /*You are required to complete this method */
    // Return the size of the largest sub-tree which is also a BST
    int largestBst(Node *root) {
       return largeBSThelper(root).maxsize;
    }
};

