dic_lr = dict()
n = int(input())
for i in range(n):
    s = str(input())
    data = s.split(' - ')
    word = data[0]
    trans = data[1]
    translation = trans.split(', ')
    for k in range(len(translation)):
        if translation[k] in dic_lr:
            dic_lr[translation[k]] = dic_lr.get(translation[k], word) + ", " + word
        dic_lr[translation[k]] = dic_lr.get(translation[k], word)
print(len(dic_lr))
for m in (sorted(dic_lr.keys())):
    print(m, "-", dic_lr[m])
