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
    test_hash = crypt.crypt(one_char_pw, salt)
    if test_hash == _hash:
        print (one_char_pw)
        sys.exit(0)
    else:
        for j in itertools.chain(range(64,91), range(97,123)):
            second_char = chr(j)
            if second_char == '@':
                second_char = ''
            two_char_pw = first_char + second_char
            test_hash = crypt.crypt(two_char_pw, salt)
            if test_hash == _hash:
                print (two_char_pw)
                sys.exit(0)
            else:
                for k in itertools.chain(range(64,91), range(97,123)):
                    third_char = chr(k)
                    if third_char == '@':
                        third_char = ''
                    three_char_pw = first_char + second_char + third_char
                    test_hash = crypt.crypt(three_char_pw, salt)
                    if test_hash == _hash:
                        print(three_char_pw)
                        sys.exit(0)
                    else:
                        for k in itertools.chain(range(64,91), range(97,123)):
                            fourth_char = chr(k)
                            if fourth_char == '@':
                                fourth_char = ''
                            four_char_pw = first_char + second_char + third_char + fourth_char
                            test_hash = crypt.crypt(four_char_pw, salt)
                            if test_hash == _hash:
                                print(four_char_pw)
                                sys.exit(0)
                                
                                
#Cut down times ALOT with new method YAYAYAYAYAY
# PASSWORD    TIMES:  crack.py       VS        crack.c
#  YES                 <1 s                      19 s
#  NO                  <1 s                      11 s
#  TF                  <1 s                      14 s
#  CA                  <1 s                      3 s 
#  nope                35 s                      33 s
#  ROFL                16 s                      14 s
