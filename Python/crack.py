import crypt
import itertools
import sys

if len(sys.argv)!=2:
    print("usage: python crack.py [hash]")
    sys.exit(1)

_hash = sys.argv[1]

salt = _hash[0:2]

for i in itertools.chain(range(64,91), range(97,123)):
    first_char = chr(i)
    if first_char == '@':
        first_char = ''
    one_char_pw = first_char
    print(one_char_pw)
    test_hash = crypt.crypt(one_char_pw, salt)
    if test_hash == _hash:
        print ("YAY")
        sys.exit(0)
    else:
        for j in itertools.chain(range(64,91), range(97,123)):
            second_char = chr(j)
            if second_char == '@':
                second_char = ''
            two_char_pw = first_char + second_char
            print(two_char_pw)
            test_hash = crypt.crypt(two_char_pw, salt)
            if test_hash == _hash:
                print ("YAY")
                sys.exit(0)
            else:
                for k in itertools.chain(range(64,91), range(97,123)):
                   third_char = chr(k)
                if third_char == '@':
                   three_char_pw = first_char + second_char + third_char
                   print(three_char_pw)
                   test_hash = crypt.crypt(two_char_pw, salt)
                   if test_hash == _hash:
                       print("YAY")
                       sys.exit(0)
