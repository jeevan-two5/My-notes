  
/*              TWO SUM

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
*/


//  method1 (using map)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp; // value -> index
        vector<int> res;

        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if(mp.find(complement) != mp.end()) {
                // found the pair
                res.push_back(mp[complement]); // index of complement
                res.push_back(i);              // current index
                return res;
            }
            mp[nums[i]] = i; // store value with its index
        }

        return res; // if no pair found
    }
};


//  method 2 ( sorting -> using two pointer approach )

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<pair<int,int>> arr;  // {value, original_index}

        // Store numbers with their original indices
        for(int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by values
        sort(arr.begin(), arr.end());

        int li = 0, ri = n - 1;
        while(li < ri) {
            int sum = arr[li].first + arr[ri].first;
            if(sum == target) {
                return {arr[li].second, arr[ri].second}; 
            }
            else if(sum < target) {
                li++;
            }
            else {
                ri--;
            }
        }

        return {}; // if no solution found
    }
};

