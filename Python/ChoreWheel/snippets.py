#def rev_str(my_str):
 #   length = len(my_str)
  #  for i in range(length - 1,-1,-1):
   #     yield my_str[i]
#
#ls = [0,1,2,3,4,5,6,7]
#
#for char in rev_str(ls):
#     print(char)

my_list = [1, 3, 6, 10]

s=(x**2 for x in my_list)

print(next(s))
print(next(s))
print(next(s))
print(next(s))
print(next(s))
print(next(s))
print(next(s))


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
