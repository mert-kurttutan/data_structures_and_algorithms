#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op);
vector<long long> max_and_min(string s, int i, int j);
long long get_maximum_value(const string &exp);




int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

vector<long long> max_and_min(vector<vector<long long>> &M, vector<vector<long long>> &m, string s, int i, int j){

  long long min = std::numeric_limits<int>::max();
  long long max = std::numeric_limits<int>::min();
  long long a, b,c,d;
  for (int k=i; k < j; k += 1){
    a = eval(M[i][k], M[k+1][j], s[2*k+1]);
    b = eval(M[i][k], m[k+1][j], s[2*k+1]);
    c = eval(m[i][k], M[k+1][j], s[2*k+1]);
    d = eval(m[i][k], m[k+1][j], s[2*k+1]);
    min = std::min({min, a, b, c, d});
    max = std::max({max, a, b, c, d});
  }
  return vector <long long> ({min, max});
}



long long get_maximum_value(const string &exp) {
  
  int n = (exp.size() + 1)/2;
  vector<vector<long long>> m(n, vector<long long> (n));
  vector<vector<long long>> M(n, vector<long long> (n));
  
  for (int i=0; i < n; i++){
    m[i][i] = int(exp[2*i])-48;
    M[i][i] = int(exp[2*i])-48;
  }
  for (int s=1; s<n; s++){
    for (int i=0; i< n-s; i++){
      int j = i+s;
      vector<long long> Mm = max_and_min(M,m,exp,i,j);
      m[i][j] = Mm[0];
      M[i][j] = Mm[1];
    }
  }
  return M[0][n-1];
}