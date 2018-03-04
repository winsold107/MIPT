events = list(map(int, input().split(" ")))
happy = list(map(int, input().split(" ")))
sad = list(map(int, input().split(" ")))

my_dict = dict()

res = 0

for e in happy:
    my_dict[e] = 1
for e in sad:
    my_dict[e] = -1
for e in events:
    if e in my_dict:
        res += my_dict[e]

# i = 0
# k = 0
#
# for i in range(len(happy)):
#     for k in range(len(events)):
#         if events[k] == happy[i]:
#             res = res + 1
#         elif events[k] == sad[i]:
#             res = res - 1
print(res)
