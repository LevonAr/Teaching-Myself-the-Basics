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
