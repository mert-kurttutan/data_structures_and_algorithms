#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size() - 1;         //left and right indices to keep track of current state in the search

  while (left + 1 < right){                         //left == right is the final point of binary search
    if (a[(left + right) / 2] < x) {
      left = (left + right) / 2;                         //if the middle element is lower than the input, look at the higher half
  }
    else if (a[(left + right) / 2] > x){
      right = (left + right) /2 ;                         //middle lement higher than the input, look at the lower half
    }

    else{
      return (left + right) / 2;                          //if equal, it's found the element, return it
    }
    //std::cout << left << " and " << right <<  " and " << x << "\n";
}
  if (a[right] == x){
    return right;
  } 
  else if (a[left] == x){
    return left;
  }
  else{
    return -1;                                   //this is reached only if an element is not found
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
    std::cout << binsrch(a, b[i]) << ' ';
  }
}
