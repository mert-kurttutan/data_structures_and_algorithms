#! /usr/bin/env python3
import sys


def reach(adj, x, y, visited_arr):
    visited_arr[x] = True

    for w in adj[x]:
        # Once target is spotted, stop searching
        if w == y:
            visited_arr[y] = True
            return 1

        # Recursive step
        if not visited_arr[w]:
            reach(adj, w, y, visited_arr)
        
        # Stop search further ngbhrs after finding target
        if visited_arr[y]:
            return 1

    return 0

if __name__ == '__main__':
    # Read input
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]

    # Input -> list of edges
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    x, y = data[2 * m:]

    # Adjancency list
    adj = [[] for _ in range(n)]
    x, y = x - 1, y - 1
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    visited_arr = [False]*n
    print(reach(adj, x, y, visited_arr))
