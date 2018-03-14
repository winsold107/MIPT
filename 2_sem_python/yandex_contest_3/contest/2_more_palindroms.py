def palindrom(str):
    rts = str
    rev_str = ""
    for c in range(len(rts)):
        rev_str = rts[c] + rev_str
    if rev_str == rts:
        ret = True
    else:
        ret = False
    return ret


s = str(input())
rev = s
size = len(s) - 1
m = 0
n = 0
k = 0
concat = ""
if (palindrom(s)):
    print("0")
else:
    for i in range(size):
        concat = rev[i] + concat
        m += 1
        rev = rev + concat
        if palindrom(rev) is True:
            break
        rev = s
    concat = ""
    print(rev)
    for j in range(1, size + 1):
        concat = rev[j] + concat
        n += 1
        rev = concat + rev
        if palindrom(rev) is True:
            break
        rev = s
    print(rev)
    concat = ""
    for l in range(1, size + 1):
        concat = rev[0 - l] + concat
        k += 1
        rev = concat + rev
        if palindrom(rev) is True:
            break
        rev = s
    print(k)
    print(rev)
    p = min(m, n)
    print(min(p, k))
