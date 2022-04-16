#! /usr/bin/env python3
# python3

# from logging import root
import sys, threading
sys.setrecursionlimit(10**6) # max depth of recursion
threading.stack_size(2**27)  # new thread will get stack of such size

class TreeOrders:
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
  def inOrderMove(self, index: int):
    '''
    Executes one step of inOrder Tree iteration in binary search tree 
    in recursive manner

    1) Left Child
    2) Key itself
    3) Rigth Child

    Parameters:
      index: int
        index of the node on which move to be done
    
    '''
    # Base case: if key is null
    if index == -1:
      return 

    self.inOrderMove(self.left[index])
    self.result.append(self.key[index])
    self.inOrderMove(self.right[index])

  def preOrderMove(self, index: int):
    '''
    Executes one step of inOrder Tree iteration in binary search tree 
    in recursive manner

    1) Node itself
    2) Left Child
    3) Rigth Child

    Parameters:
      index: int
        index of the node on which move to be done
    
    '''
    # Base case: if key is null
    if index == -1:
      return 

    self.result.append(self.key[index])
    self.preOrderMove(self.left[index])
    self.preOrderMove(self.right[index])


  def postOrderMove(self, index: int):
    '''
    Executes one step of inOrder Tree iteration in binary search tree 
    in recursive manner

    1) Left Child
    2) Rigth Child
    3) Node itself

    Parameters:
      index: int
        index of the node on which move to be done
    
    '''
    # Base case: if key is null
    if index == -1:
      return 

    self.postOrderMove(self.left[index])
    self.postOrderMove(self.right[index])
    self.result.append(self.key[index])


  def inOrder(self):
    '''
    Starts the inOrder Traversal of tree, starting from the root
    It collects the results in self.result list
    '''
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that

    root_index = 0
    self.inOrderMove(self.left[root_index])
    self.result.append(self.key[root_index])
    self.inOrderMove(self.right[root_index])
                
    return self.result

  def preOrder(self):
    '''
    Starts the preOrder Traversal of tree, starting from the root
    It collects the results in self.result list
    '''
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that

    root_index = 0
    self.result.append(self.key[root_index])
    self.preOrderMove(self.left[root_index])
    self.preOrderMove(self.right[root_index])
    return self.result

  def postOrder(self):
    '''
    Starts the postOrder Traversal of tree, starting from the root
    It collects the results in self.result list
    '''
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that

    root_index = 0
    self.postOrderMove(self.left[root_index])
    self.postOrderMove(self.right[root_index])
    self.result.append(self.key[root_index])
    return self.result

def main_thread():
	tree = TreeOrders()
	tree.read()
	print(" ".join(str(x) for x in tree.inOrder()))
	print(" ".join(str(x) for x in tree.preOrder()))
	print(" ".join(str(x) for x in tree.postOrder()))



if __name__ == "__main__":

  threading.Thread(target=main_thread).start()