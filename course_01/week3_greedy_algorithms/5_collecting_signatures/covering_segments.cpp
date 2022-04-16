#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <climits>

using std::vector;

 
// Function that returns the type ptr

struct Segment {
  int start, end;
};

bool comp(vector<Segment> a, int i, int j){                         //>: puts in increasing order
    return a[i].end > a[j].end;
}

vector<int> optimal_points(vector<Segment> &segments);

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}



vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...
  //prepare the indices for the order of the vectors a and b
  std::vector<int> indices_end(segments.size());
  std::iota(indices_end.begin(), indices_end.end(), 0);
  auto comp_a = bind(comp, segments, _1, _2);                        //bind is supercool!!
  long long result = 0;

  // sort the indices based on end points
  std::sort(indices_end.rbegin(), indices_end.rend(), bind(comp, segments, _1, _2));


  points.push_back(segments[indices_end[0]].end);      //the segment with the nearest end point is automatically the first point by greedy algorithm
  //write your code here
  for (size_t i = 1; i < segments.size(); ++i) {
    if (points.back() < segments[indices_end[i]].start){
      points.push_back(segments[indices_end[i]].end);
    }
  }
  return points;
}
