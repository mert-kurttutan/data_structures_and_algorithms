#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

int partition3(vector<int> &A);

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}


int partition3(vector<int> &A) {
  /*
  solution for the paritioning souvenirs problem using dynamical programming
  main idea: store the possiblity of this paritiion in a matrix of the dim (sum/3 + 1, n+1, n+1)
  first index is for the sum of each indiviual desired paritiion, hence stop at sum/3
  second and third indices for the number of elements in first and second partitions. No need to indicate
  the third partitions since these two imply also for the third.
  they dynamically construct the solution from the previous elements in the matrix while iterating over 
  indices.
  
    args:
      A: vector of integers to be partitioned into 3 different sets, of size n
    returns:
      boolean: whether the set A can be paritiioned into 3 subset with equal sums
  */
  
  // sum of the all items
  int sum = 0;

  for (int elem: A){
    sum += elem;
  }

  // if not divisible by 3, then it cannot be partitioned to 3 equal sums
  if (std::remainder(double(sum),3.0)!= 0.){
    return 0;
  }

  // size of axis for first and second partition indices
  int first = A.size()+1;
  int second = A.size()+1;

  // initialize 3d vector with all items being false
  vector<vector<vector<bool>>> part3(sum/3+1, vector<vector<bool>> (first, vector<bool> (second, false)));


  // initializae the items with zero weight to be true, they can be trivially obtained by setting all
  // partitions to be zero
  for (int j=0; j<first; j++){
    for(int k=0; k<second; k++){
      part3[0][j][k] = true;
    }
  }
  for (int i=1; i< (sum/3+1); i++){
    for (int j=1; j < first; j++){
      for(int k=1; k < second; k++){

        // accept any of the true previous values
        part3[i][j][k] = part3[i][j-1][k-1] || part3[i][j][k-1] || part3[i][j-1][k];

        // 3 different situations:
        bool case1=part3[i][j][k];
        bool case2=false;
        bool case3=false;
        if (i >= A[j-1])
          case1 = part3[i-A[j-1]][j-1][k];
        if (i >= A[k-1])
          case2 = part3[i-A[k-1]][j][k-1];
        if (i >= (A[j-1] + A[k-1]))
          case3 = part3[i-A[k-1] - A[j-1]][j-1][k-1];

        // if any of the combinations true, the desired partition exist
        part3[i][j][k] = (case1 || case2) || (part3[i][j][k] || case3);
      }
    }
  }

  // very last element of the matrix for the partition of the entire vector
  return int(part3.back().back().back());
}