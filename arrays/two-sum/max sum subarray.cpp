/* 
Given an integer array nums, find the subarray with the largest sum, and return its sum.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
Example 3:

Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
*/

// =================================  S  O  L  U  T  I  O  N  ===============================

// kadanes algorithm
class Solution {

public:
    int maxSubArray(vector<int>& nums) {
     int n = nums.size();
       int csum = nums[0];
        // csum = current sum
      // osum = overall sum 
       int osum = nums[0];
       for(int i = 1; i< n; i++){
            //csum += nums[i];

            if(csum >= 0){
                csum += nums[i];
                osum = max(osum, csum);
            }
           else{
            csum = nums[i];
            osum = max(osum,csum);
           }

       }
return osum;
       }
};
