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
    one_char_pw = first_char
    print(one_char_pw)
    one_char_hash = crypt.crypt(one_char_pw, salt)
    if one_char_pw == "@":
        
    
    elif one_char_hash == _hash:
        print(first_char)
        sys.exit(0)
    else:
        for j in itertools.chain(range(64,91), range(97,123)):
            second_char = chr(j)
            two_char_pw = first_char + second_char
            print(two_char_pw)
            two_char_hash = crypt.crypt(one_char_pw, salt)
            if









    #test_key = chr(i)
    #test_hash = crypt.crypt(test_key, salt)
    #if test_hash == hash:

