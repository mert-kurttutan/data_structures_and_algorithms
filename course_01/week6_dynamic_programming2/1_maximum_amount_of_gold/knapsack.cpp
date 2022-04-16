#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w, int n);

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w, n) << '\n';
}


int optimal_weight(int W, const vector<int> &w, int n) {
  //write your code here
  int current_weight = 0;
  vector<vector<int>> value(W+1, vector<int> (n+1,0));
  int val;
  // outer for loop contniues until all the items are checked
  for (int i = 1; i < w.size()+1; ++i) {
    for (int w_cur=1; w_cur < W+1; w_cur++){
      value[w_cur][i] = value[w_cur][i-1];
      if (w[i-1] <= w_cur){
       val=value[w_cur-w[i-1]][i-1] + w[i-1];
       //std::cout << "val is "<< val << std::endl;
       if (value[w_cur][i-1] < val){
        value[w_cur][i] = val;
       }
      }
      //std::cout << "item, " << w_cur << "," <<i << " is " << value[w_cur][i] << std::endl;
    }
  }
  return value[W][n];
}