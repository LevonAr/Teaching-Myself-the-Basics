while True:
    try:
        height = int(input("Height:"))
    except ValueError:
        pass
    else :
        break
while height < 0 or height > 23:
    height = int(input("Height:"))

else:
    for i in range((height-1),0,-1):
        j = i-1
        k = height-j
        print(' '*j,'#'*k)
    print('#'*(height+1))




