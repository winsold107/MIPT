import math
n = int(input())
if n == 1:
    current = 2;
elif n == 2:
    current = 3
else:
    current = 4
    i = 2
    while i < n:
        if (math.factorial(current-1)+1) % current != 0:
            current += 1
        else:
            i += 1
            current += 1
print(current)
#sudo apt-get install clang