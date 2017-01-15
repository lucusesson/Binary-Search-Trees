##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 8, Problem 1
## ***************************************************
##

import check

# collataz_sequence(n) consumes a single positive natural number, n, and produces
#   its Collatz sequence as a list.
# collatz_sequence: Nat -> (listof Nat)
# Examples:
# collatz_sequence(1) => [1]
# collatz_sequence(10) => [10,5,16,8,4,2,1]

def collatz_sequence(n):
    list_ = [n]
    while n != 1:
        if n % 2 == 0:
            n = n // 2
            list_ = list_ + [n]
        else:
            n = 3 * n + 1
            list_ = list_ + [n]
    return list_ 
        

# Test 1: n is already 1
check.expect("Q1T1", collatz_sequence(1), [1])

# Test 2: n is even
check.expect("Q1T2", collatz_sequence(10), [10,5,16,8,4,2,1])

# Test 3: n is odd
check.expect("Q1T3", collatz_sequence(21), [21, 64, 32, 16, 8, 4, 2, 1])

# Test 4: n is large even
check.expect("Q1T4", collatz_sequence(102), [102, 51, 154, 77, 232, 116, 58, 29, 88, 44, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1])

# Test 5: n is large odd
check.expect("Q1T5", collatz_sequence(105), [105, 316, 158, 79, 238, 119, 358, 179, 538, 269, 808, 404, 202, 101, 304, 152, 76, 38, 19, 58, 29, 88, 44, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1])
            
            