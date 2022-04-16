#! /usr/bin/env python3

import sys, threading
sys.setrecursionlimit(10**9) # max depth of recursion
threading.stack_size(2**27)  # new thread will get stack of such size


class Tree:
  def read(self):
    self.n = int(sys.stdin.readline())
    self.key = [-1 for i in range(self.n)]
    self.left = [-1 for i in range(self.n)]
    self.right = [-1 for i in range(self.n)]
    for i in range(self.n):
      [a, b, c] = map(int, sys.stdin.readline().split())
      self.key[i] = a
      self.left[i] = b
      self.right[i] = c



  def isBSTMove(self, index: int):
    '''
    Checks if tree (self) is ordered correctly according to binary 
    search tree format

    Parameters:
      index: int
        index of the node on which move to be done
    
    '''
    # assert dir in ['left', 'right'], "Invalid Direction"
    # Base case: if key is null
    if index == -1:
      return 

    # Go to left child
    self.isBSTMove(self.left[index])

    # Process the main node
    # Latest added node has no right child 
    if self.right[self.latest_node] == -1:
      self.isOrdered = self.isOrdered and (self.key[self.latest_node] < self.key[index])
    else:
      self.isOrdered = self.isOrdered and (self.key[self.latest_node] <= self.key[index])
    
    # Update direction, latest key based on the latest update
    # Both comparsion and relative direction of latest key determined here
    self.latest_node = index

    if not self.isOrdered:
      return

    # Move to the right
    self.isBSTMove(self.right[index])
    

  def IsBinarySearchTree(self)-> bool:
    '''
    Starts the inOrder Traversal of tree, starting from the root
    It collects the results in self.result list
    '''
    # Finish the implementation
    # You may need to add a new recursive method to do that
    self.key.append(-float('inf'))
    self.right.append(-1)
    root_index = 0
    self.latest_node = len(self.key)-1
    self.isOrdered = True


    if len(self.key) in [0,1]:
      return True


    self.isBSTMove(self.left[root_index])
    
    self.isOrdered = self.isOrdered and (self.key[self.latest_node] < self.key[root_index])
    # UPdate, direction is right since we travervse rigth subtree
    self.latest_node = root_index

    if not self.isOrdered:
      return
    
    # Traverse right subtree
    self.isBSTMove(self.right[root_index])

    self.key.pop()
    self.right.pop()
                
    return self.isOrdered



def main_thread():
  tree = Tree()
  tree.read()


  if tree.IsBinarySearchTree():
    print("CORRECT")
  else:
    print("INCORRECT")


if __name__ == "__main__":

  threading.Thread(target=main_thread).start()


