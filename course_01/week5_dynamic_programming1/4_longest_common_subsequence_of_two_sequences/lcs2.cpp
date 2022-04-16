#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b);

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}


int lcs2(vector<int> &a, vector<int> &b) {
  int n = a.size();
  int m = b.size();
  
  //table for dynamic programming, with boundary connditions implemented
  vector<vector<int>> D(n+1, vector<int>(m+1,0));

  for (int i=1; i < n+1; i++){
    for(int j=1; j < m+1; j++){
      if (a[i-1] == b[j-1]){
        D[i][j] = D[i-1][j-1] + 1;
      }
      else{
        D[i][j] = std::max({D[i-1][j-1], D[i][j-1], D[i-1][j]});
      }
    }
  }

  return D[n][m];
}