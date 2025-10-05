/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 */

//  O P T I M A L                            T C :  O (N) + O (N)          SC : O(1)
// O(1) as we are only using a list that stores a maximum of 2 elements. The space used is so small that it can be considered constant.

class Solution {

bool isValueGreaterthan_N_by_3(vector<int>&nums, int val){
        int cnt = 0;
        int n = nums.size();
    for(int i = 0 ; i < n ; i++){
        if(val == nums[i]){
            cnt++;
        }
    }
    return cnt > n/3 ; 
}

public:
    vector<int> majorityElement(vector<int>& nums) {
        int val1 = nums[0];
        int cnt1 = 1;
        int val2 = nums[0];
        int cnt2 = 0;
        int i = 1;
        while(i < nums.size()){
            if(val1 == nums[i]){
                cnt1++;
            }
            else if(val2 == nums[i]){
                cnt2++;
            }
            else{
                if(cnt1 == 0){
                    val1 = nums[i];
                    cnt1 = 1;
                }
                else if(cnt2 == 0){
                    val2 = nums[i];
                    cnt2 = 1;
                }
                else{
                    cnt1--;
                    cnt2--;
                }
            }
            i++;
        }
        vector<int>arr;
        if(isValueGreaterthan_N_by_3(nums,val1) == true){
            arr.push_back(val1);
        }
        if(val1 != val2 && isValueGreaterthan_N_by_3(nums,val2) == true){
            arr.push_back(val2);
        }

        return arr;

    }
};

/*
Time Complexity: O(N) + O(N), where N = size of the given array.
Reason: The first O(N) is to calculate the count and find the expected majority element.
  The second one is to check if the expected element is the majority one or not.
  */
