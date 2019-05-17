lst = []
for i in range(10):
    lst.append(i)
for f in lst:
    print (f())
    
height = int(input("Height:"))
while height < 0 or height > 23:
    int(input("Height:"))
