num = str(input())

ff = int(num[0])
fs = int(num[1])
fth = int(num[2])

sf = int(num[3])
ss = int(num[4])
sth = int(num[5])

im_1 = ff + fs + fth
cur_1 = sf + ss + sth
im_2 = ff + fs + fth
cur_2 = sf + ss + sth

num_up = int(num)
num_d = int(num)
val_1 = ff*100+fs*10+fth
val_2 = sf*100+ss*10+sth

while cur_1 != im_1:
    num_up += 1
    val_2 += 1

    ff = int(str(num_up)[0])
    fs = int(str(num_up)[1])
    fth = int(str(num_up)[2])

    sf = int(str(num_up)[3])
    ss = int(str(num_up)[4])
    sth = int(str(num_up)[5])

    im_1 = ff + fs + fth
    cur_1 = sf + ss + sth

while cur_2 != im_2:
    num_d = num_d - 1
    val_2 -= 1

    ff = int(str(num_d)[0])
    fs = int(str(num_d)[1])
    fth = int(str(num_d)[2])

    sf = int(str(num_d)[3])
    ss = int(str(num_d)[4])
    sth = int(str(num_d)[5])

    im_2 = ff + fs + fth
    cur_2 = sf + ss + sth
if num_up - int(num) < int(num) - num_d:
    print(num_up)
elif num_up - int(num) > int(num) - num_d:
    print(num_d)
elif num_up - int(num) == int(num) - num_d == 0:
    print(num)
else:
    print(num_d)