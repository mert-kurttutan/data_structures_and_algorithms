#!/usr/bin/env python3

# Import the heap functions from python library
from heapq import heappush, heappop, heapify 
import sys
import queue
import types
import math

class DisjSet:
    def __init__(self):
        # Constructor to create and
        # initialize sets of n items
        self.rank = {}
        self.parent = {}

    def add_elem(self, elem):
        self.rank[elem] = 1
        self.parent[elem] = elem
 
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
            return
 
        # Put smaller ranked item under
        # bigger ranked item if ranks are
        # different
        if self.rank[xset] < self.rank[yset]:
            self.parent[xset] = yset
 
        elif self.rank[xset] > self.rank[yset]:
            self.parent[yset] = xset
 
        # If ranks are same, then move y under
        # x (doesn't matter which one goes where)
        # and increment rank of x's tree
        else:
            self.parent[yset] = xset
            self.rank[xset] = self.rank[xset] + 1


class Graph:

    def __init__(self, dist: types.FunctionType):
        self.dist = dist
        self.graph = []
    def add_node(self, coord):
        self.graph.append(coord)

    def Kruskal(self):
        '''
        Kruskal algorithm to construct minimuum spanning tree out of a graph object
        '''
        # Disjoint set data strcutre to store connected nodes
        connected_nodes = DisjSet()

        # Form disjoint sets of vertices
        for v in self.graph:
            connected_nodes.add_elem(v)

        # Create all possible edges out of array of nodes
        self.edges=[]
        for u1 in self.graph:
            for u2 in self.graph:
                self.edges.append((u1,u2))

        # Sort edges based on distance
        self.edges = sorted(self.edges, key=self.dist)

        # X: store all edges in Minimum spanning tree
        X = set()
        # Weight sum: sum of all weights in minimum spanning tree
        weight_sum = 0
        # Iterate through all edges to add
        for edge in self.edges:
            u,v = edge
            # Added edges
            if connected_nodes.find(u) != connected_nodes.find(v):
                X.add((u,v))
                weight_sum += math.sqrt(self.dist((u,v)))
                connected_nodes.Union(u,v)
        
        # Return set of edges in MST and sum of weights
        return X,weight_sum

if __name__ == '__main__':
    # Take inputs
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    coords = list(zip(data[1::2],data[2::2]))
    
    # All weights formed by dist funciton
    euclidean_dist= lambda a: (a[0][0]-a[1][0])**2 + (a[0][1]-a[1][1])**2

    # Initiliaze graph
    g = Graph(euclidean_dist)

    # Add nodes to graph
    for i, (a, b) in enumerate(coords):
        g.add_node((a,b))
    
    #Print sum of weights in MST
    print(g.Kruskal()[1])