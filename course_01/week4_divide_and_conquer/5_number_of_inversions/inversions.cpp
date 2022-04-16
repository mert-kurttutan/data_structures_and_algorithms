#include <iostream>
#include <vector>

using std::vector;

long long MergeSortedIntervals(vector<int>& v, int s, int m, int e);
long long MergeSort(vector<int>& v, int s, int e);
long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right);


int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << MergeSort(a, 0, a.size()-1) << '\n';
}



// the interval from [s to m] and [m+1 to e] in v are sorted
// the function will merge both of these intervals
// such the interval from [s to e] in v becomes sorted
long long MergeSortedIntervals(vector<int>& v, int s, int m, int e) {
	
  int number_of_inversion = 0;
    // temp is used to temporary store the vector obtained by merging
    // elements from [s to m] and [m+1 to e] in v
	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

  //This flag will be set true once there is an element from right interval placed in merging
  //after this step, for every element place from left interval we increase the inverison number by
  //the number of right element present in the merged interval
  int from_right=0;

	while (i <= m && j <= e) {
		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
      number_of_inversion += from_right;
			++i;
		}
		else {
      from_right++;
			temp.push_back(v[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(v[i]);
    number_of_inversion += from_right;
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];

  return number_of_inversion;

}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
long long MergeSort(vector<int>& v, int s, int e) {
  long long number_of_inversions = 0;
	if (s < e) {
		int m = (s + e) / 2;
		number_of_inversions += MergeSort(v, s, m);
		number_of_inversions += MergeSort(v, m + 1, e);
		number_of_inversions += MergeSortedIntervals(v, s, m, e);
	}

  return number_of_inversions;
}


long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);

  return number_of_inversions;
}
