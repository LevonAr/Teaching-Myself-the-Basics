credit = input("credit card number:")

pre_num_of_digits = len(credit)

num_of_digits = pre_num_of_digits-2

lst = []

for i in range(num_of_digits,-1,-2):
    j = str(int(credit[i])*2)
    if len(j)==2:
        dig_1_sObject = slice(0,1)
        dig_2_sObject = slice(1,2)
        lst.append(int(j[dig_1_sObject]))
        lst.append(int(j[dig_2_sObject]))
    else:
        lst.append(int(j))
print (lst)

sum_lst=0

for i in lst:
    sum_lst += i

print (sum_lst)

num_of_digits = num_of_digits+1

lst_2=[]

for i in range(num_of_digits,-1,-2):
    j = int(credit[i])
    lst_2.append(j)

print(lst_2)

sum_lst_2=0

for i in lst_2:
    sum_lst_2 += i

print (sum_lst_2)

check = sum_lst+sum_lst_2

slice_first_2_digits = slice(0,2)
slice_first_digit = slice(0,1)

if check%10==0:
    if pre_num_of_digits==15 & credit[slice_first_2_digits]=='34' or '37':
        print("AMEX")
    elif pre_num_of_digits==13 & credit[slice_first_digit]=='4':
        print("VISA")
    elif pre_num_of_digits==16:
        if credit[slice_first_2_digits]=='51'or'52'or'53'or'54'or'55':
            print("MASTERCARD")
        elif credit[slice_first_digit]=='4':
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
        
else:
    print("INVALID")
