#include <iostream>
#include <vector>
#include <assert.h>

int get_change(int m);

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}




int get_change(int m) {
  std::vector<int> coin({10, 5, 1});
  int n=0;
  int m_c = m;
  for (int i: coin){
    n += m_c / i ;
    m_c = m_c - (m_c/i) * i;
  }

  assert (m_c == 0);
  return n;
}