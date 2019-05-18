try :
    height = int(input("Height:"))
    while height < 0 or height > 23:
        height = int(input("Height:"))
except ValueError:
    print ("Error: type an integer")


