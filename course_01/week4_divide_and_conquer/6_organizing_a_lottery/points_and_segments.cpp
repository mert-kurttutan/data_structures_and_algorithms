#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <algorithm>

using std::vector;

struct my_point{
  int point;
  std::string kind;
  bool operator==(const my_point& other)
{
    return point == other.point;
} 
  bool operator<(const my_point& other){
    return point < other.point;
  }
  bool operator<=(const my_point& other){
    return point <= other.point;
  }
  
  bool operator>(const my_point& other){
    return point > other.point;
  }
  bool operator>=(const my_point& other){
    return point >= other.point;
  }

};

void MergeSortedIntervals(vector<my_point>& v, int s, int m, int e);
void MergeSort(vector<my_point>& v, int s, int e);

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points);
vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points);




int main() {
  int n, m;
  std::cin >> n >> m;

  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> count = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < count.size(); i++) {
    std::cout << count[i] << ' ';
  }
}

// A helper fnunction to sort a vector in ascending order
bool comp(vector<int> a, int i, int j){
    return a[i] > a[j];
}

// Function to return the indices of the sorted array
vector<int> sorted_indices(vector<int> a){

  using namespace std::placeholders; 
  
  std::vector<int> indices_a(a.size());
  std::iota(indices_a.begin(), indices_a.end(), 0);

  // sort the indices based on a
  std::sort(indices_a.rbegin(), indices_a.rend(), bind(comp, a, _1, _2));
  return indices_a;
}



void MergeSortedIntervals(vector<my_point>& v, int s, int m, int e) {
  // temp is used to temporary store the vector obtained by merging
  // elements from [s to m] and [m+1 to e] in v
	vector<my_point> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {
		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}
	}

	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];
}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
void MergeSort(vector<my_point>& v, int s, int e) {
  //if multiple elements
	if (s < e) {
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> count(points.size());
  //vector to keep ordered sequence of indices
  vector<int> seq = sorted_indices(points);
  int number_of_intervals = 0;
  
  
  //merge three vectors to iterate through
  int total_size = starts.size() + ends.size() + points.size();
  vector<std::string> merged_str;
  vector<int> value;
  for (auto elem: starts){
    value.push_back(elem);
    merged_str.push_back("left");
  }
  for (auto elem: ends){
    value.push_back(elem);
    merged_str.push_back("right");
  }
  for (auto elem: points){
    value.push_back(elem);
    merged_str.push_back("point");
  }

  //MergeSort(merged, 0, merged.size()-1);
  vector<int> seq2 = sorted_indices(value);
  int point_idx = 0;

  for (int i = 0; i < total_size; i++){
    if (merged_str[seq2[i]] == "left"){
      number_of_intervals++;
    }
    else if (merged_str[seq2[i]] == "right"){
      number_of_intervals--;
    }
    else{
      count[seq[point_idx]] += number_of_intervals;
      point_idx++;
    }
  }
  return count;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> count(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      count[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return count;
}