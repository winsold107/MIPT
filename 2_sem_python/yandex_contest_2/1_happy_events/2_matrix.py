n = int(input())
m = int(input())
#for k in range(1, n):
print([[i * k for i in range(1, m)] for k in range(1, n)])
for i in range (1, n):
    for k in range(1, m):
        print(i*k, end="")

