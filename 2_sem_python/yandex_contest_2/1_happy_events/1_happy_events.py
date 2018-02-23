f_str = input()
s_str = input()
t_str = input()
events = f_str.split(" ")
happy = s_str.split(" ")
sad = t_str.split(" ")

res = 0
i = 0
k = 0
n = 0
m = 0

for i in range(0, len(happy)):
    for k in range(0, len(events)):
        if events[k] == happy[i]:
            res = res + 1
            print("1")

for n in range(0, len(sad)):
    for m in range(0, len(events)):
        if events[m] == sad[n]:
            res = res - 1
            print("2")
print(res)
