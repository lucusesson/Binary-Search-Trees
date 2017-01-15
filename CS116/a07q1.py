##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 7, Problem 1
## ***************************************************
##

import check

# bubble_sort(lst) conusmes a list of integers, lst, and produces the same
#   list of items, but in descending order using the bubble sort algorirthm.
# bubble_sort: (listof Int) -> (listof Int)
# Examples:
# bubble_sort([])=>[]
# bubble_sort([6, -5 ,9]) => [9, 6,-5]

def bubble_sort (lst):
    return bubble_sort2(lst, 0, 1, 0)

def bubble_sort2 (lst, a, b, c):
    if b >= len(lst) or lst == []:
        if c == 0:
            return lst
        else:
            return bubble_sort2(lst, 0, 1, 0)
    elif lst[a] < lst[b]:
        lst = lst[:a] + [lst[b]] + [lst[a]] + lst[b+1:]
        return bubble_sort2(lst, a+1, b+1, c+1)
    else:
        return bubble_sort2(lst, a+1, b+1, c)

# Test 1: lst is empty
check.expect("Q1T1", bubble_sort([]), [])

# Test 2: lst if in ascending order
check.expect("Q1T2", bubble_sort([1,2,3]), [3,2,1])

# Test 3: lst is already in descending order
check.expect("Q1T3" , bubble_sort([65, 32, 21, 20, 4, -100]),
             [65, 32, 21, 20, 4, -100])

# Test 4: lst has one element
check.expect("Q1T4", bubble_sort([1]), [1])

# Test 5: lst is long and unordered
check.expect("Q1T5", bubble_sort([3,5,1,55,2,31,67,90,0]),
             [90,67,55,31,5,3,2,1,0])

# Test 6: largest element is at the start of the list
check.expect("Q1T6", bubble_sort([1,-1,100,1000]), [1000, 100, 1, -1])
             
        
    
        
