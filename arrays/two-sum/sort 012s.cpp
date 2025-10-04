/*
Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

 

Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]

*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
      int i = 0 ,j = 0, k = nums.size()-1;
        //j to i - 1    0's
      // i to k ( unknown)
        // i to k-1 

        while(i <=k){
            if(nums[i] == 0){
                swap(nums[i],nums[j]);
                j++;
                i++;
            }
            else if(nums[i] == 1){
                i++;
            }
            else{
                swap(nums[i],nums[k]);
                k--;
            }
        }

    }
}; 
