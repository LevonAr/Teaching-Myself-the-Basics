import sys

if len(sys.argv)!=2:
    print("Usage: python vigenere.py [k]")
    sys.exit(1)

key = sys.argv[1]

key_list = []

for i in key:
    if i.isupper():
        a = ord(i)-65
    elif i.islower():
        a = ord(i)-97
    else:
        sys.exit(1)
