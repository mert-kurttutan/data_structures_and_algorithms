#include <iostream>
#include <cassert>
#include <vector>

using std::vector;
/*
Given a sequence of increasing integers which mmight include duplicate values, find the first index for the place
at which the input integer occurs

Parameters:
  Integer: 
  Array, taken to be vector class

Returns:
  desired index


*/


int binary_search_unique(const vector<int> &a, int x);
int binary_search_duplicate(const vector<int> &a, int x);
int binsrch(const vector<int> &a, int x);

  

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search_duplicate(a, b[i]) << ' ';
  }
}

int binsrch(const vector<int> &a, int x)
{
  int lo = 0;
  int hi = (int)a.size()-1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (x <= a[mid]) {
      hi = mid;
    }
    else {
      lo = mid + 1;
    }
  }
  // if a[lo] is k
  if (a[lo] == x){ return lo;}
        
  else {return -1;}
}

  int binary_search_duplicate(const vector<int> &a, int x){

    int idx = binsrch(a, x);
    int j = idx;
    if (idx == -1){ return -1;}

    while (a[j] == a[idx] and j >= 0){
      j--;
    }
    return j + 1;
  }