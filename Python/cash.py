while True:
    try:
        change = float(input("change owed:"))
        if change>0:
            break
        else:
            pass

    except ValueError:
        pass

slice_change = int(change)

difference = change-slice_change

dollar_change = slice_change/.25

pre_whole_num_change = difference*100

whole_num_change = round(pre_whole_num_change)

quarters = whole_num_change//25

quarter_rem = whole_num_change%25

dimes = quarter_rem//10

dime_rem = quarter_rem%10

nickels = dime_rem//5

nickel_rem = dime_rem%5

pennies = nickel_rem//1

total = int(dollar_change+quarters+dimes+nickels+pennies)

print (total)
