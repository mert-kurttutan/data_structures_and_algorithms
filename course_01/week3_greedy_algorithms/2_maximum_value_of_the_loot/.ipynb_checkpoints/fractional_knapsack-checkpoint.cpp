#include <iostream>
#include <vector>
// #include <bits/stdc++.h>
#include <numeric>
#include <algorithm>

double get_optimal_value(int capacity, std::vector<int> weights, std::vector<int> values) ;


int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  std::vector<int> values(n);
  std::vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}




double get_optimal_value(int capacity, std::vector<int> weights, std::vector<int> values) {
  double value = 0.0;
  std::vector<int> indices(values.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.rbegin(), indices.rend(), [&](int A, int B) -> bool {
                return (double(values[A]) / double(weights[A])) < (double(values[B]) / double(weights[B]));
            });
  double item_portion;
  int rem_capacity = capacity;
  for (int i: indices){
    item_portion = std::min(1., double(rem_capacity) / double(weights[i]));
    rem_capacity = rem_capacity - int(item_portion * weights[i]);
    value += values[i] * item_portion;
    if (rem_capacity <= 0){
      break;
    }
  }
  
  return value;
}