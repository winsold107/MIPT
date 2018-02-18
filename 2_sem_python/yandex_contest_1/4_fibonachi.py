n = int(input())
res = 1
t = 1
i = 3
if n == 0:
    fib = 0
elif n == 1:
    fib = 1
elif n == 2:
    fib = 1
else:
    while i <= n:
        fib = res + t
        t = res
        res = fib
        i += 1
print(fib)