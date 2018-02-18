num = str(input())
ff = int(num[0])
fs = int(num[1])
fth = int(num[2])
cur = ff + fs + fth
sf = int(num[3])
ss = int(num[4])
sth = int(num[5])
if cur <= sf:
    sf = cur
    ss = 0
    sth = 0
elif cur == sf + 1:
    if 100 - ss * 10 + sth < ss * 10 + sth:
        sf = cur
        ss = 0
        sth = 0
    else:
        if ss <= 9:
            sth = cur - sf - ss
        else:
            sf = cur
            ss = 0
            sth = 0
elif cur <= sf + 18:
    if ss >= (cur - sf):
        ss = cur - sf
        sth = 0
    else:
        if cur - sf <= ss:
            ss = cur - sf
            sth = 0
        elif cur - sf <= ss + 9:
            sth = cur - sf - ss
        else:
            ss = cur - sf - 9
            sth = 9
else:
    sf = cur - 18
    ss = 9
    sth = 9
res = str(ff) + str(fs) + str(fth) + str(sf) + str(ss) + str(sth)
print(res)
