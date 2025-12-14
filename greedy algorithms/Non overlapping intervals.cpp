
static bool comp(vector<int>&a, vector<int>&b){
  return a[1] < b[1];
}

int f(vector<vector<int>>&I){ // I - intervals
  int n = I.size();
  sort(I.begin(), I.end());
  int ans = 1;
  int prev = I[0][1];
  for(int i = 1 ; i < I.size() ; i++){
    if(I[i][0] >= prev) {  // > , >= in both questions this and N meetings
      prev = I[i][1];
      ans++;
    }
  }
  return (n - ans);
}
