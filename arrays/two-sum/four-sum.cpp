/*
       ---------------- FOUR SUM -----------------
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

 

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]

*/
// method 1 
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> res;

        sort(nums.begin(), nums.end()); // sort for easier duplicate handling

        for(int i = 0; i < n - 3; i++) {
            // skip duplicate nums[i]
            if(i > 0 && nums[i] == nums[i-1]) continue;

            for(int j = i + 1; j < n - 2; j++) {
                // skip duplicate nums[j]
                if(j > i + 1 && nums[j] == nums[j-1]) continue;

                long long newTarget = (long long)target - nums[i] - nums[j];
                int li = j + 1, ri = n - 1;

                while(li < ri) {
                    long long sum = nums[li] + nums[ri];
                    if(sum < newTarget) {
                        li++;
                    }
                    else if(sum > newTarget) {
                        ri--;
                    }
                    else {
                        // found a quadruplet
                        res.push_back({nums[i], nums[j], nums[li], nums[ri]});

                        // skip duplicates for nums[li]
                        while(li < ri && nums[li] == nums[li+1]) li++;
                        // skip duplicates for nums[ri]
                        while(li < ri && nums[ri] == nums[ri-1]) ri--;

                        li++;
                        ri--;
                    }
                }
            }
        }

        return res;
    }
};

//                               -----------------------------------------------------------------------------------








