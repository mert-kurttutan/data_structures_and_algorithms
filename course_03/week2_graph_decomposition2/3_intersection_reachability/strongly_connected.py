#! /usr/bin/env python3

import sys
sys.setrecursionlimit(200000)


from collections import defaultdict

class Graph:

    def __init__(self, size):
        self.size = size
        self.adj = defaultdict(list)

    # Add edge into the graph
    def add_edge(self, v, w):
        self.adj[v].append(w)

    # dfs
    def dfs(self, d, is_visited):
        is_visited[d] = True

        for i in self.graph[d]:
            if not is_visited[i]:
                self.dfs(i, is_visited)

    def fill_order(self, d, is_visited, stack):
        is_visited[d] = True
        for i in self.graph[d]:
            if not is_visited[i]:
                self.fill_order(i, is_visited, stack)
        stack = stack.append(d)

    # transpose the matrix
    def reverse(self):
        g = Graph(self.size)

        for i in self.graph:
            for j in self.graph[i]:
                g.add_edge(j, i)
        return g

    # Print stongly connected components
    def print_scc(self):
        stack = []
        is_visited = [False] * (self.size)

        for i in range(self.size):
            if not is_visited[i]:
                self.fill_order(i, is_visited, stack)

        G_R = self.reverse()

        is_visited = [False] * (self.size)

        result = 0
        while stack:
            i = stack.pop()
            if not is_visited[i]:
                G_R.dfs(i, is_visited)
                result += 1
               # print("")
        return result




if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    g = Graph(n)
    
    for i in range(len(edges)):
        edges[i] = map(lambda x: x-1, edges[i])
    for i in range(m):
        g.add_edge(*edges[i])

    
    print(g.print_scc())
