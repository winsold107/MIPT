def UnicalSymbols(s):
    a = dict()
    for i in range(len(s)):
        if s[i] in a:
            continue
        else:
            a[s[i]] = s.count(s[i])
    ret = False
    if len(a) >= 4:
        ret = True
    return ret


def AnyDigit(s):
    for i in range(len(s)):
        if s[i].isdigit():
            return True
        else:
            continue
    return False


def AnyLetter(s):
    for i in range(len(s)):
        if s[i].isalpha():
            return True
        else:
            continue
    return False


def AnyUpper(s):
    for i in range(len(s)):
        if s[i].isupper():
            return True
        else:
            continue
    return False


def AnyLower(s):
    for i in range(len(s)):
        if s[i].islower():
            return True
        else:
            continue
    return False


string = str(input())
strin = string.lower()
NoAnna = strin.find("anna")
Eight = len(string)
if (AnyUpper(string)) and (AnyLower(string)) and\
        (AnyDigit(string)) and (AnyLetter(string)) and\
        (NoAnna == -1) and (Eight >= 8) and\
        (UnicalSymbols(strin)):
        print("strong")
else:
    print("weak")
