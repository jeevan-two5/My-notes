class Solution {
public:
    vector<vector<int>> kSum(vector<int>& nums, int target, int k, int start = 0) {
        vector<vector<int>> res;
        int n = nums.size();

        // base case: 2Sum using two pointers
        if (k == 2) {
            int li = start, ri = n - 1;
            while (li < ri) {
                long long sum = (long long)nums[li] + nums[ri];
                if (sum == target) {
                    res.push_back({nums[li], nums[ri]});
                    // skip duplicates
                    while (li < ri && nums[li] == nums[li+1]) li++;
                    while (li < ri && nums[ri] == nums[ri-1]) ri--;
                    li++;
                    ri--;
                }
                else if (sum < target) {
                    li++;
                }
                else {
                    ri--;
                }
            }
            return res;
        }

        // recursive case: reduce kSum to (k-1)Sum
        for (int i = start; i < n - k + 1; i++) {
            // skip duplicates
            if (i > start && nums[i] == nums[i-1]) continue;

            // recursive call for k-1 sum
            vector<vector<int>> tmp = kSum(nums, target - nums[i], k - 1, i + 1);

            // append nums[i] to each solution
            for (auto& t : tmp) {
                t.insert(t.begin(), nums[i]);
                res.push_back(t);
            }
        }

        return res;
    }

    // Wrapper functions
    vector<vector<int>> twoSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return kSum(nums, target, 2, 0);
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return kSum(nums, 0, 3, 0); // target fixed = 0
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return kSum(nums, target, 4, 0);
    }
};
