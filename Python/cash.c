while True:
    try:
        change = float(input("change owed:"))
        break

    except ValueError:
        pass

while change<0:
    change = float(input("change owed:"))



change = float(input("change owed:"))

print(change)

slice_change = int(change)

print(slice_change)

difference = change-slice_change

dollar_change = slice_change/.25

print(difference)

pre_whole_num_change = difference*100

print(pre_whole_num_change)

whole_num_change = round(pre_whole_num_change)

print(whole_num_change)

quarters = whole_num_change//25

print(quarters)

quarter_rem = whole_num_change%25

print(quarter_rem)

dimes = quarter_rem//10

print(dimes)

dime_rem = quarter_rem%10

print(dime_rem)

nickels = dime_rem//5

print(nickels)

nickel_rem = dime_rem%5

print(nickel_rem)

pennies = nickel_rem//1

print(pennies)

total = int(dollar_change+quarters+dimes+nickels+pennies)

print (total)










  

  
:) cash.py exists
:) input of 0.41 yields output of 4
:) input of 0.01 yields output of 1
:) input of 0.15 yields output of 2
:( input of 1.6 yields output of 7
    expected "7\n", not "3\n"
:( input of 23 yields output of 92
    expected "92\n", not "0\n"
:( input of 4.2 yields output of 18
    expected "18\n", not "2\n"
:( rejects a negative input like -.1
    expected program to reject input, but it did not
:( rejects a non-numeric input of "foo"
    expected program to reject input, but it did not
:( rejects a non-numeric input of ""
    expected program to reject input, but it did not






