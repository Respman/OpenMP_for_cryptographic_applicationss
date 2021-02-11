#! /usr/bin/env python3

from itertools import *

n = 400000

def main():

    alph = "abcdefghijklmnopqrstuvwxyz"
    num = "0123456789"
    #alph = 'abcdefghijk'
    #num = '012'
    mas = [alph, alph, alph, num]

    out = []
    comb = set(permutations(mas))

    amnt = 0
    crt = 0
    crt_name = 0
    name = './keys/file'
    txt = '.txt'
    for mas in [[list(j) for j in i] for i in comb]:
        a1, a2, a3, a4 = mas
        for i in product(a1, a2, a3, a4):
            
            if (crt == 0):
                f = open((name+str(crt_name)+txt),'w')
                crt_name += 1

            i = list(i)
            # my key is da****t1
            i.insert(0,'d')
            i.insert(1,'a')
            i.insert(6,'t')
            i.insert(7,'1')
            passw = "".join(i)
            f.write(passw+'\n')
            
            crt += 1
            amnt += 1
            if (crt == n):
                crt = 0
                f.close()

    print(f"amount of keys: {amnt}\n")


if __name__ == '__main__':
    main()
