#!/usr/bin/env python3

# Import the heap functions from python library
from heapq import heappush, heappop, heapify 
import sys
import queue

# A class for Min Heap
class MinHeap:
      
    # Constructor to initialize a heap
    def __init__(self):
        self.heap = [] 
        self.v_to_idx = []
    def parent(self, i):
        return int((i-1)/2)
      
    # Inserts a new key 'k'
    def insertKey(self, value, item):
        # Use tuple to compare based on custom values
        heappush(self.heap, (value, item))           
  
    # Decrease value of key at index 'i' to new_val
    # It is assumed that new_val is smaller than heap[i]
    def decreaseKey(self, i, new_val):
        # Since tuples are immutable
        _, item = self.heap[i]
        self.heap[i]  = new_val, item
        while(i != 0 and self.heap[self.parent(i)][0] > self.heap[i][0]):
            # Swap heap[i] with heap[parent(i)]
            self.heap[i] , self.heap[self.parent(i)] = (
            self.heap[self.parent(i)], self.heap[i])
              
    # Method to remove minium element from min heap
    def extractMin(self):
        return heappop(self.heap)
  
    # This functon deletes key at index i. It first reduces
    # value to minus infinite and then calls extractMin()
    def deleteKey(self, i):
        self.decreaseKey(i, float("-inf"))
        self.extractMin()
  
    # Get the minimum element from the heap
    def getMin(self):
        return self.heap[0]


class Graph:

    def __init__(self, size):
        self.size = size
        self.graph = [[] for _ in range(self.size)]

    # Add edge into the graph
    def add_edge(self, s, d, w):
        self.graph[s].append((d,w))

    # dfs
    def dfs(self, d, visited_vertex):
        visited_vertex[d] = True
        print(d, end='')
        for i,_ in self.graph[d]:
            if not visited_vertex[i]:
                self.dfs(i, visited_vertex)

    def distance(self, s, t):
        # Initiliaze the distance list and source's distance
        dist = [float('inf')]*self.size
        dist[s] = 0

        # User Binary Heap for priority queue of distances of vertices
        #H = MinHeap()
        H = [i for i in dist]


        # Dijkstra's algorithm
        for _ in range(self.size):

            # Get minimum from priority queuey based on 
            # distance from source
            min_value = min(H)
            u = H.index(min_value)
            H[u] = float('inf')

            for v,w in self.graph[u]:
                if dist[v] > (dist[u] + w):
                    # Update distance
                    dist[v] = dist[u] + w
                    
                    # Update priority queue
                    H[v] = dist[v]

        return dist


if __name__ == '__main__':
    # Take input, prerocess
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
    data = data[3 * m:]

    # Initialize graph
    g = Graph(n)

    # Add edges, adj list
    for ((a, b), w) in edges:
        g.add_edge(a-1,b-1,w)

    #Source and target nodes
    s, t = data[0] - 1, data[1] - 1

    # Distance between source and target
    result = g.distance(s,t)

    # Wheter reachable or not
    if result[t] == float('inf'):
        print(-1)
    else:
        print(result[t])
