/*653. Two Sum IV - Input is a BST

Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.
Example 1:


Input: root = [5,3,6,2,4,null,7], k = 9
Output: true
Example 2:


Input: root = [5,3,6,2,4,null,7], k = 28
Output: false*/

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */



//================================= S O L U T I O N ==========================================
class Solution {
private:
    class BSTiterator {

public:
   void pushAll(TreeNode* node){
        for(;node!=NULL;){
            mystack.push(node);
            if(reverse == true)   node = node->right;
            else node = node->left;
        }
   }
    stack< TreeNode* > mystack;
    bool reverse = true;
    BSTiterator(TreeNode* root, bool isReverse){
        reverse = isReverse;
        pushAll(root);
    }

    
    
    int next() {
        TreeNode* tmpnode = mystack.top();
        mystack.pop();
        if(!reverse) pushAll(tmpnode->right);
        else pushAll(tmpnode->left);
        return tmpnode->val;
    }
    
    bool hasNext() {
       return !mystack.empty(); 
    }
};

public:
    bool findTarget(TreeNode* root, int k) {

        if(!root) return false;
        BSTiterator l(root, false);
        BSTiterator r(root,true);
        int i = l.next();
        int j = r.next();

        while(i < j){
            if(i+j == k) return true;
            else if(i+j < k) i = l.next();
            else j = r.next();
        }
        return false;
    }
};
/// T.C:O(N)    S.C: 2*O(height)

