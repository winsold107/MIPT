def StringAmount(inp):
    counter = 0
    lin = inp.readline()
    while lin:
        counter += 1
        lin = inp.readline()
    print(counter)


def SymbolAmount(inp):
    counter = 0
    lin = inp.readline()
    minus = len(lin)
    while lin:
        counter = counter + len(lin)
        lin = inp.readline()
    print(counter - minus - 1)


def LongestString(inp):
    maximum = -999999999
    lin = inp.readline()
    minus = len(lin)
    lina = inp.readline()
    while lina:
        if len(lina) > maximum:
            maximum = len(lina)
        lina = inp.readline()
    print(maximum)


def WordsAmount(inp):
    lina = inp.readline()
    counter = 0
    lin = inp.readline()
    for i in range(len(lin)):
        a = lin.split()
        counter += len(a)
        lin = inp.readline()
    print(counter)


reader_fail = open("input.txt", 'r')
line = reader_fail.readline()
if "-m" in line:
    SymbolAmount(reader_fail)
if "-l" in line:
    StringAmount(reader_fail)
if "-L" in line:
    LongestString(reader_fail)
if "-w" in line:
    WordsAmount(reader_fail)
reader_fail.close()
