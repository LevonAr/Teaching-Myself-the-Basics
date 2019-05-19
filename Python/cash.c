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






