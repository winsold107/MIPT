s = str(input())
data = s.split(' ')
n = int(data[0])
m = int(data[1])
part = str()
for i in range(0, n):
    for k in range(0, m):
        part = part + " " + str((i+1)*(k+1))
        k += 1
    print(part)
    part = ""
    i += 1
