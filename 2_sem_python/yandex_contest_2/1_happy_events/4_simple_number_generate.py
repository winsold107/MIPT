def is_prime(value):
    if value % 2 == 0:
        return value == 2
    d = 3
    while d * d <= value and value % d != 0:
        d += 2
    return d * d > value


n = int(input())
if n == 1:
    current = 3
elif n == 2:
    current = 4
else:
    current = 4
    i = 2
    while i < n:
        if is_prime(current):
            i += 1
            current += 1
        else:
            current += 1
print(current - 1)
