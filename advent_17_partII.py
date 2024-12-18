import math


# Function to convert octal to decimal
def todec(num):
    res = 0
    power = 0
    while num > 0:
        digit = num % 10
        res += (8 ** power) * digit
        power += 1
        num //= 10
    return res


# Function to check if a number is octal
def isoct(num):
    while num > 0:
        digit = num % 10
        if digit > 7:
            return False
        num //= 10
    return True


# Main logic
if __name__ == "__main__":
    # Read input values
    a = b = c = 0

    # Reading `a`
    s = input()
    temp = ""
    for ch in s:
        if '0' <= ch <= '9':
            temp += ch
    a = int(temp) if temp else 0

    # Reading `b`
    s = input()
    temp = ""
    for ch in s:
        if '0' <= ch <= '9':
            temp += ch
    b = int(temp) if temp else 0

    # Reading `c`
    s = input()
    temp = ""
    for ch in s:
        if '0' <= ch <= '9':
            temp += ch
    c = int(temp) if temp else 0

    # Reading program
    s=input()
    s = input()
    program = []
    temp = ""
    for ch in s:
        if '0' <= ch <= '9':
            program.append(int(ch))

    print(program)

    n = len(program)
    # in_str = "65530"
    print(len(in_str))
    char_count = {}
    for ch in in_str:
        char_count[ch] = char_count.get(ch, 0) + 1

    # Iterate through potential octal values
    for iter in range(247839653009592, 247839653009592+8,1):
        # if not isoct(iter):
        #     continue
        a = iter
        result = ""
        i = 0
        while i < n:
            opcode = program[i]
            if i + 1 >= n:
                break
            operand = program[i + 1]

            # Determine the value based on the operand
            if 0 <= operand <= 3:
                val = operand
            elif operand == 4:
                val = a
            elif operand == 5:
                val = b
            elif operand == 6:
                val = c
            elif operand == 7:
                val = -1
            else:
                val = 0

            # Perform operations based on opcode
            if opcode == 0:
                num = a
                den = (1 << val)
                a = num // den
            elif opcode == 1:
                b = b ^ operand
            elif opcode == 2:
                b = val % 8
            elif opcode == 3:
                if a != 0:
                    i = operand - 2
            elif opcode == 4:
                b = b ^ c
            elif opcode == 5:
                val1 = val % 8
                result += str(val1)

            elif opcode == 6:
                num = a
                den = (1 << val)
                b = num // den
            elif opcode == 7:
                num = a
                den = (1 << val)
                c = num // den

            i += 2

        print(f"{iter}  {result}")
        #
        # sz1 = len(result)
        # match = 0
        # temp_count = char_count.copy()
        # for ch in result:
        #     if ch in temp_count and temp_count[ch] > 0:
        #         match += 1
        #         temp_count[ch] -= 1
        #     if match == 2:
        #         break
        #
        # if match == 2:
        #     print(f"The result is {result} and the value of a (in oct is) {iter}, value of a is {todec(iter)}")


