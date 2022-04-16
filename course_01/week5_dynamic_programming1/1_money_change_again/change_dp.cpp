#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vector;
// Solution of Money Change problem using dynamical programming
int get_change(int m, vector & number_of_coins);


int main() {
  int m;
  std::cin >> m;
  vector number_of_coins(m+1, -1);
  std::cout << get_change(m, number_of_coins) << '\n';
}


int get_change(int m, vector & number_of_coins) {

  //base cases
  if(m==3){
    number_of_coins[3] = 1;
    return 1;}
  else if (m < 3){
    number_of_coins[m] = m;
    return m;}

  //Dynamical Programming, if it is already found
  else if (number_of_coins[m] != -1){
    return number_of_coins[m];
  }

  //recursion
  int num_1 = get_change(m-1, number_of_coins) + 1;
  int num_3 = get_change(m-3, number_of_coins) + 1;
  int num_4 = get_change(m-4, number_of_coins) + 1;
  number_of_coins[m] = std::min({num_1, num_3, num_4});
  return number_of_coins[m];
}