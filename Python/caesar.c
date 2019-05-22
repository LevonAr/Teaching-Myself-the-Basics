import sys

if len(sys.argv)!=2:
    print("Usage: ./caesar k")
    sys.exit(1)
        
K = int(sys.argv[1])

plaintext = input("plaintext:")

polished_K = K%26
        
for i in plaintext:
    print (plaintext[i])

