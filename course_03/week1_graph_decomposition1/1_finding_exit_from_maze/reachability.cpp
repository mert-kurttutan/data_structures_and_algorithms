#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;


int reach(vector<vector<int> > &adj, int x, int y, vector<int> & visited) {
  // Depth first search
  int isReached = 0;
  visited.push_back(x);
  for (int ngh : adj[x]){
    if (ngh == y){
      isReached = 1;
    }
    // end of depth
    else if (std::find(visited.begin(), visited.end(), ngh) == visited.end()){
      isReached = reach(adj, ngh, y, visited);
    }
    if (isReached==1)
      break;
  }

  return isReached;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  vector<int> visited;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1, visited);
}
