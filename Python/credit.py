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







