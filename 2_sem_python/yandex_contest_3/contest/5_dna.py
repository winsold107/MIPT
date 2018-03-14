def palindrom(str):
    rev_str = ""
    for c in range(len(str)):
        rev_str = str[c] + rev_str
    return rev_str


dna = str(input())
dna = palindrom(dna)
res = ""
for i in range(len(dna)):
    if dna[i] == "A":
        res = res + "T"
    elif dna[i] == "T":
        res = res + "A"
    elif dna[i] == "G":
        res = res + "C"
    elif dna[i] == "C":
        res = res + "G"
print(res)
