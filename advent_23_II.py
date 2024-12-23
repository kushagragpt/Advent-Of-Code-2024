import sys
from collections import defaultdict


def bron_kerbosch(R, P, X, graph, cliques):
    if not P and not X:
        cliques.append(R)  # Found a maximal clique
        return

    for v in list(P):
        newR = R | {v}
        newP = {p for p in P if p in graph[v]}
        newX = {x for x in X if x in graph[v]}

        bron_kerbosch(newR, newP, newX, graph, cliques)

        P.remove(v)  # Remove v from P
        X.add(v)  # Add v to X


def main():
    # Read input
    n = 3380
    graph = defaultdict(set)
    for _ in range(n):
        s = sys.stdin.readline().strip()
        u, v = s[:2], s[3:5]
        graph[u].add(v)
        graph[v].add(u)

    # Prepare sets and run Bron-Kerbosch
    R, X, P = set(), set(), set(graph.keys())
    cliques = []
    bron_kerbosch(R, P, X, graph, cliques)

    # Find the largest clique and sort its elements
    max_clique = set()
    for clique in cliques:
        if len(clique) > len(max_clique):
            max_clique = clique
        elif len(clique) == len(max_clique):
            if sorted(clique) < sorted(max_clique):
                max_clique = clique

    # Output the largest clique in lexicographical order
    result = sorted(max_clique)
    print(",".join(result) + ",")


if __name__ == "__main__":
    main()
