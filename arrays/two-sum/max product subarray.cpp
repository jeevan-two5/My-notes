/*Given an integer array nums, find a subarray that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 */

// ================================S O L U T I O N =================================================

class Solution {
public:
    int maxProduct(vector<int>& nums) {
      //  int ans = 
    int n = nums.size();
    int cprod = 1; 
    int ans = INT_MIN;
    for(int i = 0; i< n; i++){
        cprod *= nums[i];
       ans  = max(cprod,ans );
       if(cprod == 0){
        cprod = 1;
       }
    }

    cprod =1 ;
    for(int  i = n-1 ; i >= 0 ; i--){
        cprod *= nums[i];
        ans = max(cprod , ans);
        if(cprod == 0){
            cprod = 1; 
        }
    }
    return ans;
    }
};
