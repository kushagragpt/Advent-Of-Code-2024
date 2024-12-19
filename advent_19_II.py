import sys
from collections import defaultdict


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


    s=input()

    sz=len(s)
    designs=set()
    i = 0
    while i < sz:
        temp = ""
        if 'a' <= s[i] <= 'z':
            j = i
            while j < sz and 'a' <= s[j] <= 'z':
                temp += s[j]
                j += 1
            designs.add(temp)
            i = j - 1
        i += 1
    s=input()

    ans = 0
    for i in range(1, 401):
        s = input()
        n = len(s)
        dp = [0] * (n + 1)
        dp[0] = 1

        for j in range(1, n + 1):
            for design in designs:
                length = len(design)
                if j >= length and s[j - length:j] == design and dp[j - length]:
                    dp[j] += dp[j - length]

        ans += dp[n]

    print(ans)


if __name__ == "__main__":
    main()
