#!/usr/bin/env python3

import sys


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

    def BellmanFord(self, s, dist):
        
        # Source dist = 0
        dist[s] = 0

        # User Binary Heap for priority queue of distances of vertices
        #H = MinHeap()
        H = [i for i in dist]


        update_len = 0
        is_updated = True
        # Naive relaxation-based algorithm
        while is_updated and update_len < self.size:
            is_updated = False

            # Iterate through all the edges, with adj list
            for u in range(self.size):
                for v,w in self.graph[u]:
                    if dist[v] > (dist[u] + w):
                        # At lest one edge is updated
                        is_updated = True

                        # Update distance
                        dist[v] = dist[u] + w

            
            # Count how many times it is updated
            update_len += 1

        return dist, update_len


    def is_negative_cycle(self):

        # Initiliaze the distance list
        dist = [float('inf')]*self.size

        for s in range(self.size):

            # Start from every undiscovered source
            # This will also go throug disconnected vertices
            
            if dist[s] == float('inf'):
                _, update_len = self.BellmanFord(s, dist)

                if update_len > self.size-1:
                    return 1
            

        return 0


if __name__ == '__main__':
    # Take input and prerpocess
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))

    # Initialize graph
    g = Graph(n)
    # Add edges, adj list
    for ((a, b), w) in edges:
        g.add_edge(a-1,b-1,w)

    # Print if there is a negative cycle
    print(g.is_negative_cycle())


