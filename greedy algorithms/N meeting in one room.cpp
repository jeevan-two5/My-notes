int max_meetings(int start[] , int end[] , int n){
  vector<pair<int, int>> meet;
  for(int i = 0 ; i < n; i++){
    meet.push_back( {end[i]}  ,  {start[i]}  );
  }
  sort(meet.begin() , meet.end());

  int ans = 1; prev = meet[0].first;

  for(int i = 1 ; i < n; i++ ){
    if(meet[i].second > prev) {
      ans++;
      prev = meet[i].first;
    }
  }

  return ans;
  
}
