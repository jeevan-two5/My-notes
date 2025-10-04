/* Construct a BST, implement the Insert Function
and Print the BST in sorted order.
Objective: To construct a Binary Search Tree (BST), implement the insert function,
and print the BST elements in sorted order using inorder traversal. */ 
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val){
      data = val;
      left = right = NULL;
    }
};


Node* insert(Node* root, int val){
  
  if(!root) return new Node(val);
  
  if(val < root->data) root->left = insert(root->left, val);
    
  else root->right = insert(root->right , val);

  return root;
  
}

void inorder(Node* root){
    if(!root) return ;
      inorder(root->left);
      cout<<root->data<<" ";
      inorder(root->right);
}

int main(){
  Node* root = NULL;
  vector < int > values = { 6 , 2 , 8 , 0 , 4 , 7 , 9 , 3 , 5 };
  for ( int val : values ) root = insert ( root , val );

  cout << "BST in sorted order: ";
  inorder(root);  
  cout << endl;
  return 0;
    
}
