#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
// Primitive Calculate problem: Reach a given input integer by the follow three operations
// adddition by 1, multiplication by 2, multiplication 3
// Find the sequence that gives minimum number of steps for this problemm.
// Do this by using dynamical programming.
/*
bool IsLast (vector<int> a, int n) {
    return (a.back()==n);
}
*/
vector<int> optimal_sequence(int n);
vector<int> optimal_sequence_dp(int n, vector<vector<int>> & sequence_arr);

int main() {
  int n;
  std::cin >> n;
  vector<vector<int>> sequence_arr;
  vector<int> sequence = optimal_sequence_dp(n, sequence_arr);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}


vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}


vector<int> optimal_sequence_dp(int n, vector<vector<int>> & sequence_arr) {
  /*
    solve this dynamical programming
  */
  //lambda function to detect sequence previous found  
  auto isLast= [=](vector<int> a){ return a.back()==n;};

  //see: https://www.cplusplus.com/reference/algorithm/find_if/
  vector<vector<int>>::iterator it = std::find_if (sequence_arr.begin(), sequence_arr.end(), isLast);

  //if the sequence is found before
  if (it != sequence_arr.end()){
    return *it;
  }

  //base case
  if (n==1){
    vector<int> cur{1};
    sequence_arr.push_back(cur);
    return sequence_arr.back();
  }
  
  //recursive step, measure their lengths, for determining minimal step
  vector <int> vec1, vec2, vec3;

  //if divisible by 3, this is the minimal step
  if (n % 3 == 0){
    vec3 = optimal_sequence_dp(n/3, sequence_arr);
    sequence_arr.push_back(vec3);
  }

  //otherwise compare division by 2 and addition by 1
  else{
    vec1 = optimal_sequence_dp(n-1, sequence_arr);
    int len1 = vec1.size();  
    int len2 = len1+1; //wont be maximum unless they are changed below

    if (n % 2 == 0){
      vec2 = optimal_sequence_dp(n/2, sequence_arr);
      len2 = vec2.size();
    }

    //dont use any package to pick the respective minimal vector
    // do this  manually

    if (len2 <= len1){
      sequence_arr.push_back(vec2);
    }
    else{
      sequence_arr.push_back(vec1);
    }
  }
  sequence_arr.back().push_back(n);

  return sequence_arr.back();
}