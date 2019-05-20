credit = input("credit card number:")

pre_num_of_digits = len(credit)

num_of_digits = pre_num_of_digits-2

lst = []

for i in range(num_of_digits,-1,-2):
    j = str(int(credit[i])*2)
    if len(j)==2:
        asdasd
    lst.append(j)
