##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 8, Problem 2
## ***************************************************
##

import check

# spread_it (s, n) consumes an alphabetic, non-whitespace string s and a
#    natural number n, and produces a string by using the digits in n to 
#    determine how many times the characters in s should appear.
# spread_it: Str Nat -> Str
# Examples:
# spread_it("house",12131) => "hooussse"
# spread_it("house",12001) => "hooe"

def spread_it (s, n):
    string = ""
    n = str(n)
    for x in n:
        if s != "":
            string = string + int(x)*s[0]
            s = s[1:]
    return string + s

# Test 1: number of characters in s is the same as the nunber of digits in n
check.expect("Q2T1", spread_it("house",12131), "hooussse")

# Test 2: n contains zero's
check.expect("Q2T1", spread_it("house",12001), "hooe")

# Test 3: number of characters in s is less than the nunber of digits in n
check.expect("Q2T3", spread_it("house",213211564), "hhouuusse")

# Test 4: number of characters in s is greater than the nunber of digits in n
check.expect("Q2T3", spread_it("lame", 213), "llammme")

# Test 4: n = 0
check.expect("Q2T3", spread_it("lucus", 0), "ucus")


            