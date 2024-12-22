from collections import defaultdict, deque

# Function to simulate the secret number evolution and count bananas
def calculate_bananas(inp):
    bananas = defaultdict(int)

    for num in inp:
        seen = set()
        q = deque([], 4)
        ref = 200000

        for _ in range(2000):
            # Evolve the secret number
            num = (num * 64) ^ num
            num %= 16777216

            num = (num // 32) ^ num
            num %= 16777216

            num = (num * 2048) ^ num
            num %= 16777216

            # Calculate the current value
            val = num % 10

            # Update the sliding window of price changes
            q.append(val - ref)
            ref = val

            # Check for unique sequences and update the count
            w = tuple(q)
            if w not in seen:
                bananas[w] += val
            seen.add(w)

    return max(bananas.values())

def main():
    # Read input from user
    n = int(input("Enter the number of buyers: "))
    inp = []
    print("Enter the initial secret numbers for each buyer:")
    for _ in range(n):
        inp.append(int(input()))

    # Calculate and print the maximum bananas
    max_bananas = calculate_bananas(inp)
    print("Maximum bananas:", max_bananas)

if __name__ == "__main__":
    main()
