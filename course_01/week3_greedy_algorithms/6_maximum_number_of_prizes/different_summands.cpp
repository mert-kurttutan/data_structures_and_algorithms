#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n);

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}




vector<int> optimal_summands(int n) {
  vector<int> summands;
  long long total_sum = 0;
  bool reached = false;
  bool exceeded = false;
  int i = 1;
  while(!reached and !exceeded){ 
    summands.push_back(i);
    total_sum += i;
    i++;

    reached = (total_sum == n);
    exceeded = (total_sum > n);
  }
  if (exceeded){
    summands.pop_back();
    total_sum -= i-1;
    summands.back() = (long long)(n) - total_sum + summands.back();
  }
  return summands;
}