#!/usr/bin/env python3
import sys

class Graph:

    def __init__(self, size):
        self.size = size
        self.graph = [[] for _ in range(self.size)]


    # Add edge into the graph
    def add_edge(self, s, d, w):
        self.graph[s].append((d,w))


    def get_no_arbitrage(self, arbitrage_nodes):

        # Iterate through all edges to get rid of 
        # arbitrage paths reachable from source s

        no_arbit = Graph(self.size)

        for u in range(self.size):
            if u not in arbitrage_nodes:
                for v,w in self.graph[u]:
                    if v not in arbitrage_nodes:
                        no_arbit.add_edge(u,v,w)

        return no_arbit

    # dfs
    def dfs(self, d, visited_vertex):
        visited_vertex[d] = True
        print(d, end='')
        for i,_ in self.graph[d]:
            if not visited_vertex[i]:
                self.dfs(i, visited_vertex)


    def BFS(self, s, visited_vertex=None):

        if visited_vertex is None:
            visited_vertex = [False] * self.size

        node_queue = [s]
        # Discovered nodes
        discovered = [s]
        visited_vertex[s] = True

        # Iterate through node queue
        while(len(node_queue) != 0):

            # Pop node
            u = node_queue.pop(0)

            # Iterate throug its ngh nodes
            for v,_ in self.graph[u]:
                if not visited_vertex[v]:
                    # Discover ngh nodes
                    visited_vertex[v] = True
                    node_queue.append(v)
                    discovered.append(v)

        return discovered


    def BellmanFord(self, s, dist=None, prev=None):
        '''
        Applies BellmannFord algorithm to elements updated in the self.size-th cycle
        This will be helpful when finding negative cycles
        '''
        if prev is None:
            prev = [None] * self.size

        if dist is None:
            dist = [float('inf')] * self.size
        
        # Source dist = 0
        dist[s] = 0

        # Use array to store distance values, to be extracted
        H = [i for i in dist]

        # Array of nodes updated in the last cycle
        last_updated = []
        update_len = 0

        # To check if there is update in the cycle
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

                        # Update distance and prev
                        dist[v] = dist[u] + w
                        prev[v] = u

                        if update_len == self.size-1:
                            # To track negative cycle
                            last_updated.append(v)

            
            # Count how many times it is updated
            update_len += 1

        return update_len, last_updated


    def get_neg_cycle(self, v, prev):

        u = v

        # Arrive some pnt inside negative cycle
        for _ in range(self.size):
            u = prev[u]
        
        # Iterate adn append to all the elems to list
        x_iter = prev[u]
        neg_cycle = [u]

        # Until the cycle is completed
        while (u != x_iter):
            neg_cycle.append(x_iter)

            # Move backwards
            x_iter = prev[x_iter]

        return neg_cycle




if __name__ == '__main__':
    #Take input and preprocess
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
    data = data[3 * m:]

    # Initialize graph
    g = Graph(n)

    # Add edges
    for ((a, b), w) in edges:
        g.add_edge(a-1,b-1,w)

    # Source node
    s = data[0]-1

    # Get the lastly updated vertices and last updated cycle
    update_len, last_updated = g.BellmanFord(s)

    # Collect nodes reachealb from negative ccyles
    discovered = []
    visited_vertex = [False] * g.size
    for v_0 in last_updated:
        discovered += g.BFS(v_0, visited_vertex)
    
    # Array of unique elemeents
    discovered = set(list(discovered))

    # Get the version of graph without any negative cycle nodes
    no_arbit = g.get_no_arbitrage(discovered)

    
    # BellmanFord on graph with negative arbitrage
    distance = [float('inf')] * n
    no_arbit.BellmanFord(s, distance)

    # Correct the distances for arbitrage points
    for i in discovered:
        distance[i] = float('-inf')

    # Unreachable, arbitrage and reachable points
    for i in range(g.size):
        if distance[i] == float('inf'):
            print("*")
        elif distance[i] == float('-inf'):
            print("-")
        else:
            print(distance[i])


