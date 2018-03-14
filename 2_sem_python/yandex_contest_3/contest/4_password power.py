def UnicalSymbols(s):
    a = dict()
    for i in range(len(s)):
        if s[i] in a:
            continue
        else:
            a[s[i]] = s.count(s[i])
    ret = False
    print(a)
    print(len(a))
    if len(a) >= 4:
        ret = True
    return ret

# def has_enough_unique_symbols(password):
#     a = dict()
#     for c in password:
#         a[c] = True
#     return len(a) >= 4
#

# Условие:
#
# Правила простые: сильным может считаться только тот пароль,
# в котором есть буквы в разных регистрах и цифры.
#
# Пароли длины менее 8,
# пароли состоящие менее чем из 4 уникальных символов,
# и пароли в которых встречается слово anna (в любом регистре букв) считаются слабыми.
#
#
#
# Возможно проблема в том, что условие не запрещает использовать что-то кроме букв и цифр.
# Однако все пароли, в которых нет либо букв, либо цифр - по дефолту должны быть слабыми. (кажется так)
#
# >>> 1234567&
# >>> strong
#
# >>> 1234567t
# >>> weak

# А еще, возможно потому что, ты считаешь уникальные символы уже в строке, где сделала lowercase
# Т.е. символы 'А' и 'а' будут одим и тем же символом. Хотя, вроде как, это не так.
#
# >>> aA1212121212
# >>> weak
#


string = str(input())
strin = string.lower()
one = string.islower()
two = string.isupper()
three = string.isdigit()
four = string.isalpha()
five = UnicalSymbols(string)
six = strin.find("anna") == -1
seven = len(string) >= 8
eight = string.isalnum()
if (not one) and (not two) \
        and (six) \
        and (seven) \
        and (five):
        print("strong")
else:
    print("weak")
