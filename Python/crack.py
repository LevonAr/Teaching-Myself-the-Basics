import crypt
import sys

if len(sys.argv)!=2:
    print("usage: python crack.py [hash]")
    sys.exit(1)

hash = sys.argv[1]

salt = hash[0:2]

crypt.crypt(hash, salt)
