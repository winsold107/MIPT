n = int(input())
i = 2
res = '1'
while i <= n:
    if i % 15 == 0:
        res = res+', Fizz Buzz'
    elif i % 5 == 0:
        res = res+', Buzz'
    elif i % 3 == 0:
        res = res+', Fizz'
    else:
        res = res+', '+str(i)
    i += 1
print(res)
