def check_logs_sha_1(sha_1):
    return sha_1[0:7]


def check_logs_message(message):
    a = message[::-1]
    mess = ""
    for i in range(len(a)):
        if (a[i] == "\n"):
            continue
        if (a[i] == "\t"):
            break
        else:
            mess = a[i] + mess
    return mess


reader_fail = open("input.txt", 'r')
line = reader_fail.readline()
while line:
    point = str("." * (73 - len(str(check_logs_message(line)))))
    print(str(check_logs_sha_1(line)) + point +
          str(check_logs_message(line)))
    line = reader_fail.readline()
reader_fail.close()
