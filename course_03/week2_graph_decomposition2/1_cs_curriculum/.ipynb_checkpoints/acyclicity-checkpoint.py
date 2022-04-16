#! /usr/bin/env python3

import sys

def explore(adj, v, is_visited, depth_stack):

    is_visited[v] = True
    depth_stack[v] = True
    for v_ngh in adj[v]:
        if not is_visited[v_ngh]:

            # Recursive step
            is_cyclic = explore(adj,v_ngh, is_visited, depth_stack)
            # After exploring branch of v, remove from depth_stack
            depth_stack[v_ngh] = False

            # If cycle is detected, return immediately
            if is_cyclic:
                return True
        else:
            # If visited node is current depth_stack -> it is a cycle
            if depth_stack[v_ngh]:
                return True
    return False

def acyclic(adj, is_visited, depth_stack):

    for v in range(len(adj)):
        if not is_visited[v]:
            
            # Explore branch of v
            is_cyclic = explore(adj,v,is_visited, depth_stack)

            # After exploring branch of v, remove from depth_stack
            depth_stack[v] = False
            if is_cyclic:
                return 1
            
    return 0

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)

    is_visited = [False]*n
    depth_stack = [False]*n
    print(acyclic(adj, is_visited, depth_stack))
