#include <iostream>

long long lcm_naive(int a, int b);
long long lcm_fast(int a, int b);
int gcd_Euclid(int a, int b);

int main() {
  int a, b;
  std::cin >> a >> b;
  long long lc_mul = (long long)(a)* (long long)(b / gcd_Euclid(a,b));
  std::cout <<  lc_mul << std::endl;
  return 0;
}



long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_Euclid(int a, int b){
  int rem, small, big;
  big = std::max(a,b);
  small = std::min(a,b);
  rem = big % small;
  
  if (rem ==0){
    return small;
  }
  else{
    return gcd_Euclid(small, rem);
  }
}