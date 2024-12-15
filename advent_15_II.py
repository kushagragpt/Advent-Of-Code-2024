import sys
from collections import deque

sys.setrecursionlimit(10 ** 6)

# Definitions for movements
dr = [0, 0, 1, -1]
dc = [1, -1, 0, 0]


def findbox(a, i, j, b, d):
    n = len(a)
    m = len(a[0])
    visit = [[False for _ in range(m)] for _ in range(n)]
    q = deque()
    comp = []
    q.append((i, j))
    visit[i][j] = True

    while q:
        cur = q.popleft()
        r, c = cur
        comp.append(((r, c), a[r][c]))
        if a[r][c] == '[' and not visit[r][c + 1]:
            visit[r][c + 1] = True
            q.append((r, c + 1))
        elif a[r][c] == ']' and not visit[r][c - 1]:
            visit[r][c - 1] = True
            q.append((r, c - 1))

        nr, nc = r + b, c + d
        if (a[nr][nc] == '[' or a[nr][nc] == ']') and not visit[nr][nc]:
            visit[nr][nc] = True
            q.append((nr, nc))

    return comp


def move(a, comp, di, dj):
    for it in comp:
        r, c = it[0]
        if a[r + di][c + dj] == '#':
            return False
    for it in comp:
        r, c = it[0]
        a[r][c] = '.'
    for it in comp:
        r, c = it[0]
        a[r + di][c + dj] = it[1]
    return True


def findpar(node, par):
    if node == par[node]:
        return node
    par[node] = findpar(par[node], par)
    return par[node]


def ubs(u, v, par, size):
    ulp_u = findpar(u, par)
    ulp_v = findpar(v, par)
    if ulp_v == ulp_u:
        return
    if size[ulp_u] < size[ulp_v]:
        par[ulp_u] = ulp_v
        size[ulp_v] += size[ulp_u]
    else:
        par[ulp_v] = ulp_u
        size[ulp_u] += size[ulp_v]


def main():
    n, m = 50, 50
    a = [['.' for _ in range(2 * m)] for _ in range(n)]

    for i in range(n):
        temp = input().strip()
        for j in range(m):
            if temp[j] == '#':
                a[i][2 * j] = '#'
                a[i][2 * j + 1] = '#'
            elif temp[j] == '.':
                a[i][2 * j] = '.'
                a[i][2 * j + 1] = '.'
            elif temp[j] == '@':
                a[i][2 * j] = '@'
                a[i][2 * j + 1] = '.'
            elif temp[j] == 'O':
                a[i][2 * j] = '['
                a[i][2 * j + 1] = ']'

    sz = 20000
    x, y = 20, 1000

    # Initialize the grid
    temp = []
    aesehi = input().strip()
    # Read the grid row by row
    for i in range(x):
        row = input().strip()
        if len(row) != y:
            raise ValueError(f"Row {i + 1} does not have exactly {y} characters.")
        temp.append(list(row))

    # Flatten the grid into a moves list
    moves = [temp[i][j] for i in range(x) for j in range(y)]

    for i in range(n):
        for j in range(m):
            print(a[i][2 * j] + a[i][2 * j + 1], end="")
        print()
    print()

    r, c = -1, -1
    for i in range(n):
        for j in range(2 * m):
            if a[i][j] == '@':
                r, c = i, j
                break

    for i in range(sz):
        if moves[i] == '^':
            if a[r - 1][c] == '.':
                a[r][c], a[r - 1][c] = a[r - 1][c], a[r][c]
                r -= 1
            elif a[r - 1][c] == '#':
                continue
            else:
                temp = findbox(a, r - 1, c, -1, 0)
                temp.append(((r, c), '@'))
                if move(a, temp, -1, 0):
                    r -= 1
        elif moves[i] == 'v':
            if a[r + 1][c] == '.':
                a[r][c], a[r + 1][c] = a[r + 1][c], a[r][c]
                r += 1
            elif a[r + 1][c] == '#':
                continue
            else:
                temp = findbox(a, r + 1, c, 1, 0)
                temp.append(((r, c), '@'))
                if move(a, temp, 1, 0):
                    r += 1
        elif moves[i] == '<':
            if a[r][c - 1] == '.':
                a[r][c], a[r][c - 1] = a[r][c - 1], a[r][c]
                c -= 1
            elif a[r][c - 1] == '#':
                continue
            else:
                j = c - 1
                while a[r][j] in [']', '[']:
                    j -= 1
                if a[r][j] == '#':
                    continue
                else:
                    for k in range(j, c):
                        a[r][k] = a[r][k + 1]
                    a[r][c] = '.'
                    c -= 1
        elif moves[i] == '>':
            if a[r][c + 1] == '.':
                a[r][c], a[r][c + 1] = a[r][c + 1], a[r][c]
                c += 1
            elif a[r][c + 1] == '#':
                continue
            else:
                j = c + 1
                while a[r][j] in ['[', ']']:
                    j += 1
                if a[r][j] == '#':
                    continue
                else:
                    for k in range(j, c, -1):
                        a[r][k] = a[r][k - 1]
                    a[r][c] = '.'
                    c += 1

        print(moves[i])
        print(i + 1)
        for x in range(n):
            for y in range(2 * m):
                print(a[x][y], end="")
            print()
        print()

    ans = 0
    for i in range(n):
        for j in range(2*m):
            if a[i][j] == '[':
                ans += 100 * i + j
    print(ans)


if __name__ == "__main__":
    main()
