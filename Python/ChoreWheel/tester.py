if len(sys.argv)!=2:
    print("Usage: python vigenere.py [k]")
    sys.exit(1)

key = sys.argv[1]
key_list = []

for i in key:
    if i.isupper():
        a = ord(i)-65
        key_list.append(a)
    elif i.islower():
        a = ord(i)-97
        key_list.append(a)
    else:
        print("error: use only alphabetical letters as your key")
        sys.exit(1)
        

new_toy = itertools.cycle(key_list)




print (next(new_toy))
print (next(new_toy))
print (next(new_toy))

