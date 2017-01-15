##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 8, Problem 3
## ***************************************************
##

import check

# char_matrix (n, m, word) consumes two natural numbers n and m, and a non-empty, 
#    non-whitespace string word and prints an m by n matrix by repeatedly using
#    the string word.
# char_matrix: Nat Nat Str -> None
# Effects: prints an m by n matrix by repeatedly using the string word.
# Examples:
#   char_matrix(4,6,"yoshi") will print:
#   yoshiy
#   oshiyo
#   shiyos
#   hiyosh

# char_matrix(1,7,"overdrive") will print:
#   overdri


def char_matrix (n, m, word):
    new = word * (n*m)
    for x in range(n):
        print(new[0:m])
        new = new[m:]
        
        
# Test 1:
check.set_screen("prints an m by n matrix by repeatedly using the string word")
check.expect("Q3T1", char_matrix(4,6,"yoshi"), None)

# Test 2:
check.set_screen("prints an m by n matrix by repeatedly using the string word")
check.expect("Q3T2", char_matrix(1,7,"overdrive"), None)

# Test 3:
check.set_screen("prints an m by n matrix by repeatedly using the string word")
check.expect("Q3T3", char_matrix(5,1,"wet"), None)

# Test 4:
check.set_screen("prints an m by n matrix by repeatedly using the string word")
check.expect("Q3T4", char_matrix(1,1,"lucus"), None)
