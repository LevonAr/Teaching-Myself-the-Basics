height = int(input("Height:"))
while height < 0 or height > 23:
    height = int(input("Height:"))
if isinstance(height, int):
    for i in range((height-1),0,-1):
        j = i-1
        k = height-j
        print(' '*j,'#'*k)
    print('#'*(height+1))


