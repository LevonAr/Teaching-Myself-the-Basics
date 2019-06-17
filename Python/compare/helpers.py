def lines(a, b):
    lines_list_A = str.splitlines(a)

    lines_list_B = str.splitlines(b)

    if len(lines_list_A) > len(lines_list_B):
        list_len = len(lines_list_B)                
    elif len(lines_list_B) > len(lines_list_A):        
        list_len = len(lines_list_A)
    elif len(lines_list_A) == len(lines_list_B):
        list_len = len(lines_list_A)
        
    line_matches_list = []

    for i in range(len(lines_list_A)):
        if lines_list_A[i] == lines_list_B[i]:        
            line_matches_list.append(lines_list_A[i])
