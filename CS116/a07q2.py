##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 7, Problem 2
## ***************************************************
##

import check

# sym_tri_num (n) consumes a natural number n and produces a list of all 
#    symmetric trinary numbers of length n. Where the list is in increasing
#    numerical order.
# sym_tri_num: Nat -> (listof Nat)
# Examples:
# sym_tri_num(1) => ['0', '1', '2']
# sym_tri_num(3) => ['000','010','020','101','111','121','202','212','222']

def sym_tri_num (n):
    num = "0" * n
    middle = len(number) // 2
    if n % 2 == 0:
        return make_list_even(num, [num], 1, 0, -1)
    else:
        return make_list_odd(num, [num], middle, middle - 1, middle + 1, 0)


def make(str, x):
    if add(number) == len(number) * 2:
        return make("0" + str + "0")
    elif 

    


def add(n):
    if n == "":
        return 0
    else:
        return int(n[0]) + add(n[1:])
    
    