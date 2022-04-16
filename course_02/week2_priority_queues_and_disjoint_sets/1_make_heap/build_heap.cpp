#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void SiftDown(int i){
    // given heap_array, it applies siftdown to node i
    // args:
    //  - int i: the node to be sifted down
    //  - vector<int> heap_array: array to stores heap data structure
    // returns:
    //  - indices swapped (this is for the particular task of this file)
    //  - (-1,-1) if there is no swap anymore
    // applies siftdown function to node i
    // index convention  used to represent is based on heap array convention

    int max_index = i;

    // Assign left child
    int l = 2*i+1;           

    if ((l < data_.size()) && (data_[l] < data_[max_index]))
      max_index = l;
    
    // Assign right child
    int r = 2*i+2;
    if ((r < data_.size()) && (data_[r] < data_[max_index]))
      max_index = r;

    if (i != max_index){
      // swap the nodes i and max_index
      int temp = data_[i];
      data_[i] = data_[max_index];
      data_[max_index] = temp;

      // push the new pair for swap indices
      swaps_.push_back(pair <int,int> (std::min({max_index, i}), std::max({max_index, i})));

      SiftDown(max_index);
    }
    

  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps_naive() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

  void GenerateSwaps_fast() {
    swaps_.clear();
    // efficient implementation of generating swaps 
    // Go down from to up. 
    // That this methods works can be shown inductively
    // assume that from some level below, it is heap-ordered
    // then siftdown from this level does not change heap-orderedness
    // and puts the current node to appropriate place
    for (int i = data_.size()/2; i >= 0; --i)
      SiftDown(i);
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps_fast();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
