 //     =================== J U M P    G A M E  -  II  =====================

/*
You are given a 0-indexed array of integers nums of length n. You are initially positioned at index 0.

Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at index i, you can jump to any index (i + j) where:

0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach index n - 1. The test cases are generated such that you can reach index n - 1.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [2,3,0,1,4]
Output: 2 
  */





//=================================== B R U T E ---------- T C : O ( 2 ^ N )  ---- S C ; O ( N ) ===========

int f(vector<int>&nums , int i){
  if( i >= nums.size()-1) return 0;
  if(nums[i] == 0) return INT_MAX;
  int min_step = INT_MAX;

  for(int jump = 1; jump <= nums[i] ; ++jump ){
    int X = f(nums,   i + jump);

    if( X != INT_MAX) min_step = min(min_step , 1 + X);
  }
  return min_step;
}

int ff(vector<int>&nums){
  returtn f(nums,0);
}





// ====================================- B E T T E R   -------------- T C : O ( N ^ 2 ) ----- S C : O(N)

  int f(int index , vector<int>& nums, vector<int>&dp){
    int n = nums.size();
    if(index >= n-1) return 0;
    if(dp[index] != -1) return dp[index];

    int farthest_distance = min(n , index + nums[index]);

    int minsteps = INT_MAX;

    for(int p = index + 1; p <= farthest ; p++){
      int X = f( p , nums , dp);
      if( X != INT_MAX)  minsteps = min( minsteps, 1 + X );
    }
    return dp[index] = minstep;
  }

  int ff(vector<int>&nums){
    int n = nums.size();
    vector<int>dp(n,-1);
    return f(0,nums,dp);
  }

// ===================================== O P T I M A L       S O L U T I O N -------------- T C : O ( N ) &  SC : O ( 1 )  ===================== 
int jumps(vector<int>&nums){
   int jumps = 0, farthest = 0, currEnd = 0;

  for(int i = 0 ; nums.size()-1 ; ++i){
      farthest = max( farthest , i + nums[i] );

      if( i == currEnd){ 
          jumps++;
          currEnd = farthest;
      }
    
  }
  return jumps;

}
