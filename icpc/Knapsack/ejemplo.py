def print_dp():
    for i in range(len(dp)):
        for j in range(len(dp[0])):
            print(f"{dp[i][j]:2d}", end=' ')
        print()
    print()


print_dp()


dp = [[0 for _ in range(8)] for _ in range(5)]


V = [0,1,4,5,7]
W = [0,1,3,4,5]

w_max = 7

for i in range(1, len(V)):
    for w in range(1, w_max+1):
        if W[i] <= w:
            dp[i][w] = max(dp[i-1][w], dp[i-1][w-W[i]] + V[i])
            print(f"set dp[{i}][{w}] = max(dp[{i-1}][{w}], dp[{i-1}][{w-W[i]}] + {V[i]}) = {dp[i][w]}")
        else:
            dp[i][w] = dp[i-1][w]
            print(f"set dp[{i}][{w}] = dp[{i-1}][{w}] = {dp[i][w]}")
print(f"Final: {dp[-1][-1]}")

print_dp()
