#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::queue;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int maxHeight_func_fast(std::vector<Node> nodes, int root, int n);
int maxHeight_func(std::vector<Node> nodes, int n);




int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  int root;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;

    //index of the root node, to be used for finding height
    if (parent_index == -1)
      root = child_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }
  int maxHeight = maxHeight_func_fast(nodes, root, n);
    
  std::cout << maxHeight << std::endl;
  return 0;
}





int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}


int maxHeight_func(std::vector<Node> nodes, int n){
// Replace this code with a faster implementation
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }

  return maxHeight;
}

int maxHeight_func_fast(std::vector<Node> nodes, int root_int, int n){
  // Computation of the height of a n-ary tree using queue data structure
  // NO recursion is used
  
  // initialize the height coutn
  int maxHeight = 0;

  // to keep track of current children
  queue<Node*> q;

  // start with root
  Node * root = &nodes[root_int];
  q.push(root);

  // NULL will always be in the front as long as there is children
  q.push(NULL);

  while (!q.empty()){
    Node* temp = q.front();

    // pop at every iteration
    q.pop();

    // when the all chidlren at the current level are exhausted
    if (temp == NULL){
      maxHeight++;
    }

    // when there is still children at the current level
    if (temp != NULL){
      // iterate over all children
      for (Node* child: temp->children){
        q.push(child);
      }
    }
    else if (!q.empty()){
      q.push(NULL);
    }
    
  }
    
  return maxHeight;
}