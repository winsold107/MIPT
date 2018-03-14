from __future__ import print_function
def StringAmount(inp):
    counter = 0
    lin = inp.readline()
    while lin:
        counter += 1
        lin = inp.readline()
    print(counter, end = " ")


def SymbolAmount(inp):
    counter = 0
    lin = inp.readline()
    while lin:
        counter = counter + len(lin)
        lin = inp.readline()
    print(counter, end = " ")


def LongestString(inp):
    maximum = -999999999
    lina = inp.readline()
    while lina:
        probel = lina.count(" ")
        tab = lina.count("\t")
        slog = probel + tab
        a = len(lina)
        if slog + len(lina) > maximum:
            maximum = len(lina)
        lina = inp.readline()
    print(maximum - 1, end = " ")


def WordsAmount(inp):
    counter = 0
    lin = inp.readline()
    for i in range(len(lin)):
        a = lin.split()
        counter += len(a)
        lin = inp.readline()
    print(counter, end=" ")


reader_fail = open("input.txt", 'r')
line = reader_fail.readline()
if "-l" in line:
    StringAmount(reader_fail)
reader_fail.close()
reader_fail = open("input.txt", 'r')
line = reader_fail.readline()
if "-w" in line:
    WordsAmount(reader_fail)
reader_fail.close()
reader_fail = open("input.txt", 'r')
line = reader_fail.readline()
if "-m" in line:
    SymbolAmount(reader_fail)
reader_fail.close()
reader_fail = open("input.txt", 'r')
line = reader_fail.readline()
if "-L" in line:
    LongestString(reader_fail)
reader_fail.close()
