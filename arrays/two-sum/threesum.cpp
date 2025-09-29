/*
                    ---------THREE SUM---------
                    
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.

 */

//  METHOD 1 (using set to get unique triplets)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        int target = 0;
        vector<vector<int>> res;
        set<vector<int>> uniqueSet; // to avoid duplicates

        sort(nums.begin(), nums.end()); // sorting helps in skipping duplicates

        for(int i = 0; i < n - 2; i++) {
            int nt = target - nums[i];
            int li = i + 1, ri = n - 1;

            while(li < ri) {
                int sum = nums[li] + nums[ri];
                if(sum < nt) {
                    li++;
                }
                else if(sum > nt) {
                    ri--;
                }
                else {
                    // we found a triplet
                    vector<int> triplet = {nums[i], nums[li], nums[ri]};
                    uniqueSet.insert(triplet); // store only unique triplets
                    li++;
                    ri--;
                }
            }
        }

        // move unique triplets from set to result vector
        for(auto &triplet : uniqueSet) {
            res.push_back(triplet);
        }

        return res;
    }
};


// method2  (using two while loops for li, ri)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        int target = 0;
        vector<vector<int>> res;

        sort(nums.begin(), nums.end()); // sort first

        for(int i = 0; i < n - 2; i++) {
            // skip duplicate nums[i]
            if(i > 0 && nums[i] == nums[i-1]) continue;

            int nt = target - nums[i];
            int li = i + 1, ri = n - 1;

            while(li < ri) {
                int sum = nums[li] + nums[ri];
                if(sum < nt) {
                    li++;
                }
                else if(sum > nt) {
                    ri--;
                }
                else {
                    // found a valid triplet
                    res.push_back({nums[i], nums[li], nums[ri]});

                    // skip duplicate nums[li]
                    while(li < ri && nums[li] == nums[li+1]) li++;
                    // skip duplicate nums[ri]
                    while(li < ri && nums[ri] == nums[ri-1]) ri--;

                    li++;
                    ri--;
                }
            }
        }

        return res;
    }
};


