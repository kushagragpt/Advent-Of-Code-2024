import sys
from collections import deque

# Constants for grid dimensions
n = 101
m = 103


# Robot class equivalent to the struct in C++
class Robot:
    def __init__(self):
        self.px = 0
        self.py = 0
        self.vx = 0
        self.vy = 0


# Directions for BFS (up, down, left, right)
dr = [1, -1, 0, 0]
dc = [0, 0, 1, -1]


# BFS function to count connected components
def bfs(pos, visit, i, j):
    q = deque()
    q.append((i, j))
    visit[i][j] = True

    while q:
        r, c = q.popleft()
        for k in range(4):
            nr, nc = r + dr[k], c + dc[k]
            if 0 <= nr < n and 0 <= nc < m and not visit[nr][nc] and pos[nr][nc] == '#':
                visit[nr][nc] = True
                q.append((nr, nc))


# Main function
def main():
    # Reading input
    a = []
    for i in range(500):
        robot=Robot()
        s=input()
        parts=s.split()
        pvals=list(map(int,parts[0].split('=')[1].split(',')))
        vvals=list(map(int,parts[1].split('=')[1].split(',')))
        px,py=pvals
        vx,vy=vvals
        robot.px = px
        robot.py=py
        robot.vx=vx
        robot.vy=vy
        a.append(robot)

    # Simulate for 8000 timesteps
    for t in range(1, 8001):
        pos = [['.' for _ in range(m)] for _ in range(n)]  # Initialize grid

        # Update robot positions
        for robot in a:
            robot.px = (robot.px + robot.vx + n) % n
            robot.py = (robot.py + robot.vy + m) % m
            pos[robot.px][robot.py] = '#'  # Mark robot's position

        # Count connected components using BFS
        visit = [[False for _ in range(m)] for _ in range(n)]
        comp = 0

        for i in range(n):
            for j in range(m):
                if pos[i][j] == '#' and not visit[i][j]:
                    comp += 1
                    bfs(pos, visit, i, j)

        # Print results if components are <= 300
        if comp <= 300:
            print(f"Time is {t}")
            print(f"components are {comp}")
            for row in pos:
                print(''.join(row))
            print()


if __name__ == "__main__":
    main()
