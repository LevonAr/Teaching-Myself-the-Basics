import sys

if len(sys.argv)!=2:
    print("Usage: ./caesar k")
    sys.exit(1)

K = int(sys.argv[1])

plaintext = input("plaintext:")

polished_K = K%26

ciphertext = ""

for i in plaintext:
    if i.isupper():
        j = chr(ord(i) + polished_K)
        if j > 90:
            j = j-26
    elif i.islower():
        j = chr(ord(i) + polished_K)
        if j > 122:
            j = j -26
    else:
        j = i

    ciphertext = ciphertext + j

print (ciphertext)
