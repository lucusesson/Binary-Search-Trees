##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 9, Problem 3
## ***************************************************
##

import check

# country_stats(pos, input_file) consumes a natural number greater than zero, pos,
#   and a non-empty string representing the input file name, called input_file, 
#   and produces a string. This string represents the information about the country
#   at the index postion pos.
# country_stats: Nat Str -> Str
# Examples:
# country_stats(-5, “country_data.csv”) => None
# country_stats(0, “country_data.csv”) => "afghanistan,446000000,3759000000,29928987"

def country_stats(pos, input_file):
    f = open(input_file)
    x = pos
    y = 1
    next_str = f.readline()
    while x != 0 and y != 0:
        if next_str == "":
            y = 0
        else:
            x = x - 1
            next_str = f.readline()
    if y == 0:
        return None
    else:
        return next_str[:-1]

# Test 1:
check.expect("Q3T1", country_stats(-5, "country_data.csv"), None)

# Test 2:
check.expect("Q3T2", country_stats(0, "country_data.csv"), "afghanistan,446000000,3759000000,29928987")

# Test 3:
check.expect("Q3T3", country_stats(500, "country_data.csv"), None)

# Test 4:
check.expect("Q3T4", country_stats(10, "country_data.csv"), "argentina,33780000000,22060000000,39537943")
