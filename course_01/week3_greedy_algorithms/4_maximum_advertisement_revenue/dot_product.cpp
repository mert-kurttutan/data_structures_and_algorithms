#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

using std::vector;

 
// Function that returns the type ptr
bool comp(vector<int> a, int i, int j){
    return a[i] < a[j];
}

long long max_dot_product(vector<int> a, vector<int> b);


int main() 
{
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}


long long max_dot_product(vector<int> a, vector<int> b) {
  // write your code here
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...
  //prepare the indices for the order of the vectors a and b
  std::vector<int> indices_a(b.size()), indices_b(b.size());
  std::iota(indices_a.begin(), indices_a.end(), 0);
  std::iota(indices_b.begin(), indices_b.end(), 0);
  auto comp_a =  bind(comp, a, _1, _2);                        //bind is supercool!!
  long long result = 0;


  // sort the indices based on a and b
  std::sort(indices_a.rbegin(), indices_a.rend(), bind(comp, a, _1, _2));
  std::sort(indices_b.rbegin(), indices_b.rend(), bind(comp, b, _1, _2));
  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[indices_a[i]]) * b[indices_b[i]];
  }
  return result;
}