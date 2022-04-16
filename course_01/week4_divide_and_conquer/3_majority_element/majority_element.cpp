#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
/*
Majority Element (by divide-and-conquer technique)
-will use recursion method
-based on the idea that if the there is majority element of the whole sequence, then the
-one of the two half sequence must have this as its majority element as well.

*/
int get_majority_element(vector<int> &a, int left, int right) ;
int count(vector<int> &a, int x, int left, int right);


int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  int result = (get_majority_element(a, 0, a.size()-1) != -1);
  std::cout << result << '\n';
}


int count(vector<int> &a, int x, int left, int right){
  /*
  helper function for the majority element finding algorithm
  parameters: 
    - a: vector object in which an element to be found
    - x: the element to be searched in vector a
    - (left, right): the range of indices for which x is searched
  returns:
    - number of times x occurs inside vector a
  */
  int res=0;
  for (int i=left; i <= right; i++){
    if (a[i] == x){res++;}            //incrase when x is found
  }
  return res;
}



int get_majority_element(vector<int> &a, int left, int right) {
  /*
  the function for finding the majorith element, the element that occurs more than size/2
  inside an array
  parameters:
   - a: the vector object of which the majority element is to be found
   - (left,right): the range of indices in which majority element is found
  returns:
   - -1 if there is no maojrity element
      or the value of majority element if it is found
  */
  int mid = (left + right ) / 2;     //middle element

  //first base case: if the array of length 1, maojrity element is the one element
  if (left == right) {return a[left];}

  //2nd base case: fi the array of lenght 2, majority element is obvious
  else if (left == right - 1){
    if (a[left] == a[right]){return a[left];}
    else {return -1;}
  }

  //3rd base case: array of length 3, it still cannot be decided recursively
  // so decied to choose this to be also base case
  //this chooses the majority element by brute force
  else if (left == right - 2){
    if (a[left] == a[right]){
      return a[left];
    }
    else if (a[left] == a[right-1]){
      return a[left];
    }
    else if (a[left+1] == a[right]){
      return a[left+1];
    }
    return -1;
  }

  //recursive part
  int res1 = get_majority_element(a, left, mid);
  int res2 = get_majority_element(a, mid + 1, right);

  //if they have the same maojrity element, the resultant majority element is the same
  //if they both have no majority element, then there is no majority element, proof by contradiction
  if (res1 == res2){return res1;}  

  //if only res1 == -1
  else if (res1 == -1){
    if(count(a, res2, left, right)> double(right - left+1) / 2.){
      return res2;
    }
    return -1;
  }

  //if only res2 == -1
  else if (res2 == -1){
    if (count(a, res1, left, right) > double(right - left+1) / 2.){
      return res1;
    }
    return -1;
  }

  //if both have majority element, different ones,
  //then compare the total occurences of each majority element
  else if (count(a, res1, left, right) > double(right - left+1) / 2.){
    return res1;
  }
  else if (count(a, res2, left, right) > double(right -left+1) / 2.){
    return res2;
  }
  else{
    return -1;
  }
}


