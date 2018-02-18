n = int(input())
t = n
res = int()
for i in range(0, n // 10 + 1):
    for k in range(0, t // 5 + 1):
        res += 1
    t -= 10
print(res)
