/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
  */

// INTUITION
/*
Initialize 2 variables:

Count –  for tracking the count of element

Element – for which element we are counting

Traverse through the given array.

If Count is 0 then store the current element of the array as Element.

If the current element and Element are the same increase the Count by 1.

If they are different decrease the Count by 1.

The integer present in Element should be the result we are expecting */

// Optimal Approach: Moore’s Voting Algorithm:
class Solution {

 private:
 int findValidCandidate(vector<int>&nums){
        int val = nums[0];
        int cnt = 1;
        for(int i = 1; i< nums.size();i++){
            if(val == nums[i]) cnt++;
            else{
                cnt--;
            }
            if(cnt == 0){
                val = nums[i];
                cnt = 1;
            }
        }
        return val;
 }   
public:
    int majorityElement(vector<int>& nums) {
        return findValidCandidate(nums);
       /*  OR
           val = findValidCandidate(nums);
           int cnt = 0;
           for(int i = 0; i< nums.size();i++){
               if(val == nums[i]) cnt++;
           }
           if( cnt > nums.size()/2 ) return val;
           else return -1;
       */
    }
};

// TC : O(N) SC: O(1)
  
