#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

int number_of_components(vector<vector<int> > &adj);
void explore(vector<vector<int>> &adj, int v, vector<bool> & visited, vector<int> &CC_idx, int cc);
vector<int> DFS(vector<vector <int>> &adj);

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
  std::cout << number_of_components(adj);
}



void explore(vector<vector<int>> &adj, int v, vector<bool> & visited, vector<int> &CC_idx, int cc){
  visited[v] = true;
  CC_idx[v] = cc;
  for (int ngh : adj[v]){
    if (!visited[ngh]){
      explore(adj, ngh, visited, CC_idx, cc);
    }
  }
}

vector<int> DFS(vector<vector <int>> &adj){
  int cc = 1;
  // before start nothingis visited
  vector<bool> visited(adj.size(), false);
  vector<int> CC_idx(adj.size(), 0);

  for (int v=0; v < adj.size(); v++){
    if (!visited[v]){
      explore(adj, v, visited, CC_idx, cc);
      cc++;
    }
  }
  return CC_idx;
}




int number_of_components(vector<vector<int> > &adj) {
  vector<int> CC_idx = DFS(adj);
  return *std::max_element(CC_idx.begin(), CC_idx.end());
}