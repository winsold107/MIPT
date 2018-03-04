def palindrom(str):
    rev_str = ""
    for c in range(len(str)):
        rev_str = str[c] + rev_str
    print(rev_str)
    if rev_str == str:
        ret = True
    else:
        ret = False
    return ret


s = str(input())
size = len(s)//2 + 1
i = 0
m = 0
concat = ""
if (palindrom(s)):
    print("0")
else:
    for i in range(size):
        concat = s[i] + concat
        m += 1
        print(concat)
        s = s + concat
        if palindrom(s):
            #print(m)
            break
        elif m == size:
            print(m)
