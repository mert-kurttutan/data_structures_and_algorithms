#! /usr/bin/env python3

import sys



def explore(adj, v, is_visited, order):
    # v is visited
    is_visited[v] = True
    for v_ngh in adj[v]:
        if not is_visited[v_ngh]:
            explore(adj, v_ngh, is_visited, order)

    # Post order search
    order.insert(0,v)


def dfs(adj, is_visited, order):
    #write your code here

    for v in range(len(adj)):

        if not is_visited[v]:
            explore(adj, v, is_visited, order)

def toposort(adj):
    is_visited = [False] * len(adj)
    order = []
    #write your code here
    dfs(adj, is_visited, order)
    return order

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
    order = toposort(adj)
    for x in order:
        print(x + 1, end=' ')

