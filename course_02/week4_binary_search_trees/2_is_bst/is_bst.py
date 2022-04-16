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



  def isBSTMove(self, index: int, dir: str):
    '''
    Checks if tree (self) is ordered correctly according to binary 
    search tree format

    Parameters:
      index: int
        index of the node on which move to be done
    
    '''
    assert dir in ['left', 'right'], "Invalid Name for Direction"

    # Base case: if key is null
    if index == -1:
      return 
    
    self.isBSTMove(self.left[index], 'left')

    if dir == 'left':
      self.isOrdered = self.isOrdered and (self.recent_key < self.key[index])

    elif dir == 'right':
      self.isOrdered = self.isOrdered and (self.recent_key <= self.key[index])
      
    self.recent_key = self.key[index]

    if not self.isOrdered:
      return


    self.isBSTMove(self.right[index], 'right')

  def IsBinarySearchTree(self)-> bool:
    '''
    Starts the inOrder Traversal of tree, starting from the root
    It collects the results in self.result list
    '''
    self.recent_key = -float('inf')
    self.isOrdered = True
    # Finish the implementation
    # You may need to add a new recursive method to do that

    root_index = 0
    if len(self.key) == 0:
      return True
    self.isBSTMove(self.left[root_index], 'left')
    self.isOrdered = self.isOrdered and (self.recent_key < self.key[root_index])
    self.recent_key = self.key[root_index]

    if not self.isOrdered:
      return

    self.isBSTMove(self.right[root_index], 'right')
                
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

# def main():
#   nodes = int(sys.stdin.readline().strip())
#   tree = []
#   for i in range(nodes):
#     tree.append(list(map(int, sys.stdin.readline().strip().split())))
#   if IsBinarySearchTree(tree):
#     print("CORRECT")
#   else:
#     print("INCORRECT")

