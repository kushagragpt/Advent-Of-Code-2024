from heapq import heappush, heappop

directions = [(0, 1), (-1, 0), (0, -1), (1, 0)]  # E, N, W, S


def parse_maze(maze):
    start = end = None
    for i, row in enumerate(maze):
        for j, cell in enumerate(row):
            if cell == 'S':
                start = (i, j)
            elif cell == 'E':
                end = (i, j)
    return start, end


def dijkstra_best_paths(maze, start, end):
    rows, cols = len(maze), len(maze[0])
    priority_queue = []
    heappush(priority_queue, (0, start[0], start[1], 0, [(start[0], start[1])]))  # cost, x, y, dir, path
    visited = {}
    min_cost = float('inf')
    best_paths = []

    while priority_queue:
        cost, x, y, dir, path = heappop(priority_queue)

        # Skip if already visited with lower cost
        if (x, y, dir) in visited and visited[(x, y, dir)] < cost:
            continue

        visited[(x, y, dir)] = cost

        # Check if the end tile is reached
        if (x, y) == end:
            if cost == 143580:
                best_paths.append(path)

            continue

        # Forward movement
        nx, ny = x + directions[dir][0], y + directions[dir][1]
        if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] != '#':
            heappush(priority_queue, (cost + 1, nx, ny, dir, path + [(nx, ny)]))

        # Rotate clockwise
        new_dir = (dir + 1) % 4
        heappush(priority_queue, (cost + 1000, x, y, new_dir, path[:]))

        # Rotate counterclockwise
        new_dir = (dir - 1) % 4
        heappush(priority_queue, (cost + 1000, x, y, new_dir, path[:]))

    return best_paths, min_cost


def count_best_path_tiles(maze):
    start, end = parse_maze(maze)
    best_paths, min_cost = dijkstra_best_paths(maze, start, end)

    best_tiles = set()
    for path in best_paths:
        for tile in path:
            best_tiles.add(tile)

    return len(best_tiles), best_tiles


def visualize_best_paths(maze, best_tiles):
    maze_grid = [list(row) for row in maze]
    for x, y in best_tiles:
        if maze_grid[x][y] not in ('S', 'E'):
            maze_grid[x][y] = 'O'
    return [''.join(row) for row in maze_grid]

def read_maze_input():
    print("Enter the maze row by row (use 'S' for start, 'E' for end, and '#' for walls):")
    maze = []
    while True:
        row = input()
        if row.strip() == '':  # End input when an empty line is entered
            break
        maze.append(row)
    return maze

if __name__ == "__main__":
    maze = read_maze_input()
    print(maze)
    count, best_tiles = count_best_path_tiles(maze)
    print("Number of tiles part of at least one best path:", count)

    best_paths_grid = visualize_best_paths(maze, best_tiles)
    print("\nBest Paths Grid:")
    print("\n".join(best_paths_grid))