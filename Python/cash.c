change = float(input("change owed:"))

slice_change = change//1

difference = change-slice_change

whole_num_change = difference*100

quarters = whole_num_change//25

quarter_rem = whole_num_change%25

dimes = quarter_rem//10

dime_rem = quarter_rem%10

nickels = dime_rem//5

nickel_rem = dime_rem%5

pennies = nickel_rem

total = quarters+dimes+nickels+pennies

print (total)






