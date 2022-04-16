#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

string largest_number(vector<string> a);
bool compare(string a, string b);

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}



bool compare(string a, string b){
  //compares the string a and b, representing numbers, based on the rule of 7th question in the hw7

  string bigger;

  if (std::stoi(a+b) < std::stoi(b+a)){
    return true;
  }
  else {
    return false;
  }
}


string largest_number(vector<string> a) {
  //write your code here
  std::stringstream ret;
  vector<string> a_c = a;
  std::sort(a_c.rbegin(), a_c.rend(), compare);
  for (size_t i = 0; i < a_c.size(); i++) {
    ret << a_c[i];
  }
  string result;
  ret >> result;
  return result;
}
