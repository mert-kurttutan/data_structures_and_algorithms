#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2);


int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}


int edit_distance(const string &str1, const string &str2) {
  int n = str1.length();
  int m = str2.length();
  vector<vector<int>> D(n+1, vector<int>(m+1));

  //boundary conditions for the dynamical programming table, see the slids
  for(int i=0;i < n+1; i++){
    D[i][0] = i;
  }
  for(int j=0; j < m+1; j++){
    D[0][j] = j;
  }

  //Use recursive relation to fill up the table of dynamical programming
  for(int i=1;i < n+1; i++){
    for(int j=1; j < m+1; j++){
      int choice;

      //whether the previous characters match
      if(str1[i-1] == str2[j-1]){
        choice = D[i-1][j-1];
      }
      else{
        choice = D[i-1][j-1] + 1;
      }

      //recursion relation
      D[i][j] = std::min({D[i][j-1]+1, D[i-1][j]+1, choice});
    }
  }

  //the final corner of the matrix is the editing distance of the full two words
  return D[n][m];
}