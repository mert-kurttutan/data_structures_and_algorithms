#!/usr/bin/env python3

class DisjSet:
    def __init__(self):
        # Constructor to create and
        # initialize sets of n items
        self.rank = {}
        self.parent = {}
        self.islands = 0

    def add_elem(self, elem):
        self.rank[elem] = 1
        self.parent[elem] = elem
        self.islands += 1
 
    # Finds set of given item x
    def find(self, x):
         
        # Finds the representative of the set
        # that x is an element of
        if (self.parent[x] != x):
             
            # if x is not the parent of itself
            # Then x is not the representative of
            # its set,
            self.parent[x] = self.find(self.parent[x])
             
            # so we recursively call Find on its parent
            # and move i's node directly under the
            # representative of this set
 
        return self.parent[x]
 
 
    # Do union of two sets represented
    # by x and y.
    def Union(self, x, y):
         
        # Find current sets of x and y
        xset = self.find(x)
        yset = self.find(y)
 
        # If they are already in same set
        if xset == yset:
            # No change in number of islands
            return
 
        # Put smaller ranked item under
        # bigger ranked item if ranks are
        # different
        if self.rank[xset] < self.rank[yset]:
            self.islands += -1
            self.parent[xset] = yset
 
        elif self.rank[xset] > self.rank[yset]:
            self.islands += -1
            self.parent[yset] = xset
 
        # If ranks are same, then move y under
        # x (doesn't matter which one goes where)
        # and increment rank of x's tree
        else:
            self.islands += -1
            self.parent[yset] = xset
            self.rank[xset] = self.rank[xset] + 1

# Import the heap functions from python library
from heapq import heappush, heappop, heapify 
import sys
import queue
import types
import math

# A class for Min Heap

class Graph:


    def __init__(self, dist: types.FunctionType):
        self.dist = dist
        self.graph = []
    def add_node(self, coord):
        self.graph.append(coord)

    def Kruskal_cluster(self, N):

        connected_nodes = DisjSet()

        # Form disjoint sets of vertices
        for v in self.graph:
            connected_nodes.add_elem(v)

        self.edges=[]
        for u1 in self.graph:
            for u2 in self.graph:
                self.edges.append((u1,u2))

        # Sort edges based on distance
        self.edges = sorted(self.edges, key=self.dist)

        # Collect edges in a set
        X = set()
        # Iterate through edges
        for edge in self.edges:
            u,v = edge

            if connected_nodes.find(u) != connected_nodes.find(v):

                # Stop if number of islands is high enough and return distnace between different islands
                if connected_nodes.islands <= N:
                    return X, math.sqrt(self.dist((u,v)))

                X.add((u,v))
                connected_nodes.Union(u,v)

                
        
        return X,weight_sum

if __name__ == '__main__':
    # Take inputs, preprocess
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    coords = list(zip(data[1:-1:2],data[2:-1:2]))

    # Distance threshold and distance function
    dist_threshold = data[-1]
    euclidean_dist= lambda a: (a[0][0]-a[1][0])**2 + (a[0][1]-a[1][1])**2

    # Initiliaze the graph
    g = Graph(euclidean_dist)

    # Add nodes
    for i, (a, b) in enumerate(coords):
        g.add_node((a,b))
    
    # Print number of disconneced components
    print(g.Kruskal_cluster(dist_threshold)[1])