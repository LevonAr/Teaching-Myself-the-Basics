change = float(input("change owed:"))

slice_change = int(change)

difference = change-slice_change

print (difference)

whole_num_change = difference*100

print(whole_num_change)

quarters = whole_num_change//25

quarter_rem = whole_num_change%25

dimes = quarter_rem//10

dime_rem = quarter_rem%10

nickels = dime_rem//5

nickel_rem = dime_rem%5

pennies = nickel_rem//1

total = int(quarters+dimes+nickels+pennies)

print (total)






