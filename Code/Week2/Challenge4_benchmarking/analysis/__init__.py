import os
import re
import numpy as np

def Average(lst):
    return sum(lst) / len(lst)

directory = os.fsencode('./data')
for file in os.listdir(directory):
    fn = './data/' + os.fsdecode(file)
    filename = "./data/" + fn
    f = open(fn, "r")
    regex = ';\d+;\d+;\d+'

    values = []
    tmp = []
    ll = 0

    for line in f:
        ll += 1

        if ll == 8 or ll == 9:
            print(line[:-1])
        if ll == 10:
            print()

        if 'Mode:' in line:
            values.append(tmp)
            tmp = [line.split(':')[1][1:-1], []]

        if re.search(regex, line[:-1]):
            tmp1 = []
            for i in line[1:-1].split(';'):
                tmp1.append(int(i))
            tmp[1].append(tmp1)

    values.append(tmp)
    values = values[1:]

    for i in values:
        print(i[0])
        encrypt = []
        decrypt = []
        for j in i[1]:
            encrypt.append(j[1])
            decrypt.append(j[2])

        print("Average of encrypt: {}ms".format(Average(encrypt)))
        print("Average of decrypt: {}ms".format(Average(decrypt)))

        print("STD of decrypt: {}".format(np.std(encrypt)))
        print("STD of decrypt: {}".format(np.std(decrypt)))
        print()

