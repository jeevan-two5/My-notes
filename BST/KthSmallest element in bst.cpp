/*
  Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

Example 1:


Input: root = [3,1,4,null,2], k = 1
Output: 1
Example 2:


Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
*/

//          --------------------------O P T I M A L   S O L U T I O N -----------------------------


int inorder(TreeNode*node,int &cnt ,int k){
    if(node == NULL) return -1;
    int left = inorder(node->left,cnt,k);
    if(left!=-1) return left;
    cnt++;
    if(cnt ==k) return node->val;
 
    return inorder(node->right,cnt,k);
 }



    int kthSmallest(TreeNode* root, int k) {
        int cnt =0;
       int ans= inorder(root,cnt,k);
       return ans;
    }

// TC : O(N)  SC: O(1)
