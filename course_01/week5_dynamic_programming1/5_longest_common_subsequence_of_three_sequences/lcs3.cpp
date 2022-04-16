#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c);


int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}


int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  int n = a.size();
  int m = b.size();
  int p = c.size();
  
  //table for dynamic programming, with boundary connditions implemented
  vector<vector<vector<int>>> D(n+1, vector<vector<int>>(m+1, vector<int>(p+1,0)));
  
  //generalization of the case of two sequences
  for(int i=1; i < n+1; i++){
    for (int j=1; j < m+1; j++){
      for(int k=1; k < p+1; k++){
        if (a[i-1] == b[j-1] && b[j-1] == c[k-1]){
          D[i][j][k] = D[i-1][j-1][k-1] + 1;
        }
        else{
          D[i][j][k] = std::max({D[i][j][k-1], D[i][j-1][k-1], D[i-1][j][k-1], D[i-1][j-1][k-1],
                              D[i][j-1][k], D[i-1][j-1][k], D[i-1][j][k]});
        }
      }
    }
  }

  return D[n][m][p];
}
