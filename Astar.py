import heapq
from itertools import count

def get_neighbors():
    pass

def heuristic():
    pass

def a_star(start, goal, get_neighbors, heuristic):
    pq = []
    cnt = count()

    heapq.heappush(pq, (heuristic(start, goal), next(cnt), 0, start))

    parent = {start: None}
    g = {start: 0}

    while pq:
        f, _, cost, u = heapq.heappop(pq)

        if cost != g[u]:
            continue

        if u == goal:
            path = []
            while u is not None:
                path.append(u)
                u = parent[u]
            path.reverse()
            return path, cost

        for v, edge_cost in get_neighbors(u):
            new_cost = g[u] + edge_cost

            if v not in g or new_cost < g[v]:
                g[v] = new_cost
                parent[v] = u
                heapq.heappush(
                    pq,
                    (new_cost + heuristic(v, goal), next(cnt), new_cost, v)
                )

    return None, float('inf')
