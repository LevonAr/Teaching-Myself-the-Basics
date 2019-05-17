height = int(input("Height:"))
while height < 0 or height > 23:
    int(input("Height:"))
for i in range((height-1),0,-1):
    j = i-1
    k = height+1-j
    print(' '*j,'#'*k)
print('#'*(height+1))
