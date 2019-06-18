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
            
    return line_matches_list

def sentences(a, b):
    
    sentences_A = sent_tokenize(a)

    sentences_B = sent_tokenize(b)

    # first (not the final) form of sentence_matches_list
    sentence_matches_list_1 = []
    
    #compare
    for i in sentences_A:
        for j in sentences_B:
            if i==j:
                sentence_matches_list_1.append(i)
    
    # final form of sentence_matches_list
    # I'm just cutting out duplicates
    sentence_matches_list = set(sentence_matches_list_1)
    
    return sentence_matches_list

def substrings(a, b, n):

    #A

    # set a mark for when "a" bottoms out and cant be split into a full substring with all 'n' amount of letters
    bottom_A = len(a) - n + 1

    # first(not final) form of variable 'substrings_list_A'
    substrings_list_A_1 = []
    
    # append all substrings to new list
    for i in range(0,bottom_A):
