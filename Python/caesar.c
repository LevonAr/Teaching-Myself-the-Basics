import sys

if len(sys.argv)!=2:
    print("Usage: ./caesar k")
    sys.exit(1)
        
K = int(sys.argv[1])

plaintext = input("plaintext:")

polished_K = K%26
        
for i in plaintext:
    ciphertext[i] = plaintext[i]
    
#proper form practice
        
def bad_append(new_item, a_list=[]):
    a_list.append(new_item)
    return a_list
    
def good_append(new_item, a_list=None):
    if a_list is None:
        a_list = []
    a_list.append(new_item)
    return a_list
print (bad_append('one'))

print (bad_append('two'))

