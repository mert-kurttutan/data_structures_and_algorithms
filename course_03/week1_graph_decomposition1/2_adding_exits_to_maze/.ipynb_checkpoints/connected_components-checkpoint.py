#! /usr/bin/env python3

import sys



def explore(adj, v, visited_arr):
    visited_arr[v] = True

    for w in adj[v]:
        if not visited_arr[w]:
            explore(adj, w, visited_arr)

def number_of_components(adj, visited_arr):
    result = 0
    if len(adj) == 0:
        return 0


    for w in range(len(adj)):
        # Recursive step
        if not visited_arr[w]:
            explore(adj, w, visited_arr)
        
            result += 1

    return result

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    visited_arr = [False]*n
    cc_num = [-1]*n
    print(number_of_components(adj, visited_arr))
