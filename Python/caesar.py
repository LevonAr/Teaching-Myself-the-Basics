import sys

if len(sys.argv)!=2:
    print("Usage: ./caesar k")
    sys.exit(1)

K = int(sys.argv[1])

plaintext = input("plaintext:")

polished_K = K%26

ciphertext = ""

for i in plaintext:
    j = chr(ord(i) + polished_K)

    ciphertext = ciphertext + j

print (ciphertext)
