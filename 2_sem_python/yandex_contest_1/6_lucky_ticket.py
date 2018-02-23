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


num = str(input())

ff = int(num[0])
fs = int(num[1])
fth = int(num[2])

sf = int(num[3])
ss = int(num[4])
sth = int(num[5])

im = ff + fs + fth
cur = sf + ss + sth
num_up = int(num)
num_d = int(num)
val_1 = ff*100+fs*10+fth
val_2 = sf*100+ss*10+sth

while cur != im:
    num_up += 1
    val_2 += 1

    ff = int(str(num_up)[0])
    fs = int(str(num_up)[1])
    fth = int(str(num_up)[2])

    sf = int(str(num_up)[3])
    ss = int(str(num_up)[4])
    sth = int(str(num_up)[5])

    im = ff + fs + fth
    cur = sf + ss + sth

while cur != im:
    num_d -= 1
    val_2 -= 1

    ff = int(str(num_d)[0])
    fs = int(str(num_d)[1])
    fth = int(str(num_d)[2])

    sf = int(str(num_d)[3])
    ss = int(str(num_d)[4])
    sth = int(str(num_d)[5])

    im = ff + fs + fth
    cur = sf + ss + sth
if num_up - int(num) < int(num) - num_d:
    print(num_d)
elif num_up - int(num) > int(num) - num_d:
    print(num_up)
elif num_up - int(num) == int(num) - num_d == 0:
    print(num)
else:
    print(num_d)