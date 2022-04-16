#! /usr/bin/env python3

import sys
import queue
from collections import defaultdict
from xml.etree.ElementTree import QName

def tuple_swap(edge: tuple) -> tuple:
    '''Exchanges the elements of tuple of lenght 2'''

    return (edge[1], edge[0])

class Graph:

    def __init__(self, size):
        self.size = size
        self.adj = [[] for _ in range(self.size)]

    # Add edge into the graph
    def add_edge(self, v, w):
        self.adj[v].append(w)

    def set_adj_arr(self):
        self.adj_arr =  [[0]*self.size for _ in range(self.size)]

    # DFS
    def DFS(self, d, is_visited):
        is_visited[d] = True

        for i in self.graph[d]:
            if not is_visited[i]:
                self.dfs(i, is_visited)


    # BFS
    def BFS(self, s, is_visited):
        is_visited[s] = True

    def get_SPT(self, source):
        dist = [-1]*self.size
        dist[source] = 0

        Q = [source]

        while (len(Q) != 0):
            u = Q.pop(0)

            for u_ngh in self.adj[u]:
                if dist[u_ngh] == -1:
                    Q.append(u_ngh)
                    dist[u_ngh] = dist[u] + 1

        return dist

    def is_bartite(self):
        self.set_adj_arr()
        color = [-1]*self.size
        
        current_color = 0

        # Iterate through every vertex with BFS
        for source in range(self.size):
            # Start BFS-coloring only from undiscovered vertices
            if color[source] == -1:
                Q = [source]
                color[source] = current_color
                
                # BFS
                while (len(Q) != 0):
                    u = Q.pop(0)

                    for u_ngh in self.adj[u]:
                        if color[u_ngh] == -1:
                            Q.append(u_ngh)
                            # Connected vertices have the same color
                            color[u_ngh] = color[u]

                        # Inconsistent coloring
                        elif color[u_ngh] != color[u]:
                            return False
            
                current_color += 1

        return True


    



if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    s, t = data[2 * m] - 1, data[2 * m + 1] - 1
    g = Graph(n)
    
    for i in range(len(edges)):
        edges[i] = tuple(map(lambda x: x-1, edges[i]))

    for i in range(m):
        g.add_edge(*edges[i])
        g.add_edge(*tuple_swap(edges[i]))

    distances = g.get_SPT(s)


    
    print(distances[t])
