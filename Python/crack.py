import crypt
import itertools
import sys

if len(sys.argv)!=2:
    print("usage: python crack.py [hash]")
    sys.exit(1)

hash = sys.argv[1]

salt = hash[0:2]

for i in itertools.chain(range(65,90), range(97,122)):
    test_key = chr(i)
    test_hash = crypt.crypt(test_key, salt)
    if test_hash == hash:
        
