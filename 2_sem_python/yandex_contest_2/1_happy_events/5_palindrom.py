s = str(input())
dic_let = dict()
res = 1
m = 0
for k in range(len(s)):
    if s[k] in dic_let:
        dic_let[s[k]] = dic_let.get(s[k], res) + 1
    dic_let[s[k]] = dic_let.get(s[k], res)
for i in dic_let.keys():
    if dic_let[i] % 2 == 0:
        m += 1
if m == len(dic_let) or m == len(dic_let) - 1:
    print("YES")

else:
    print("NO")
