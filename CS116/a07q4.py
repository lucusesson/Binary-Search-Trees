##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 7, Problem 4
## ***************************************************
##

import check

# dance(status,n) consumes a list of strings, status, and a natural number, n.
#    If n is greater than 0, than each element in status is shifted down one
#    index, and the end element becomes the first element. Once n == 0, the 
#    function returns the new status.
# dance: (listof Str) Nat -> (listof Str)
# Requires: 2 <= n <= 12

def dance(status, n):
    if n == 0:
        return status
    else:
        zero = status[0]
        one = status[1]
        two = status[2]
        three = status[3]
        status = [three] + [zero] + [one] + [two]
        return dance(status,n-1)
    
# churras2(status, dice,x) consumes a list of strings, status, representing the 
#   intial block colours, a list of the number between 2 and 12 inclusive,
#   called dice, and a natural number, x, where x represents which 
#   round needs to be executed. The numbers in dice are the 
#   sums of two dice values after being rolled, and the list dice has a 
#   length of 5. The function does not produce anything, 
#   but instead prints the list of block colous at the end
#   of each of the rounds, until every block is either red or every block is
#   green. Once this happens, the function prints a completion message. 
# churras2: (listof Str) (listof Nat) Nat -> None
# Effects: In purpose statement
# Requires: Status is length 4, Dice is length 5, x starts as 0

def churras2(status,dice,x):
    if (list(filter(lambda x: x == 'red', status)) == [] or list(filter(lambda x: x == 'green', status)) == []) and x == 0:
        print(status)
        print("Let's eat. We are all very very hungry!")
    elif list(filter(lambda x: x == 'red', status)) == [] or list(filter(lambda x: x == 'green', status)) == []:
        print("Let's eat. We are all very very hungry!")
    elif x == 0:
        print(status)
        return churras2(status,dice,x+1)
    elif x == 1:
        status[0] = "green"
        status[2] = "green"
        status = dance(status,dice[0])
        print(status)
        return churras2(status,dice[1:],x+1)
    elif x == 2:
        status[0] = "green"
        status[1] = "green"
        status = dance(status,dice[0])
        print(status)
        return churras2(status,dice[1:],x+1)        
    elif x == 3:
        if status[0] == 'red' or status[2] == 'red':
            status[0] = "green"
            status[2] = "green"
            status = dance(status,dice[0])
            print(status)
            return churras2(status,dice[1:],x+1)
        else:
            status[0] = "red"
            status = dance(status,dice[0])
            print(status)
            return churras2(status,dice[1:],x+1)
    elif x == 4:
        if status[0] == "green" and status[1] == "green":
            status[0] = 'red'
            status[1] = 'red'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1)
        elif status[0] == "red" and status[1] == "green":
            status[0] = 'green'
            status[1] = 'red'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1) 
        elif status[0] == "green" and status[1] == "red":
            status[0] = 'red'
            status[1] = 'green'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1)
        elif status[0] == "red" and status[1] == "red":
            status[0] = 'green'
            status[1] = 'green'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1)   
    else:
        if status[0] == "green" and status[2] == "green":
            status[0] = 'red'
            status[2] = 'red'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1)
        elif status[0] == "red" and status[2] == "green":
            status[0] = 'green'
            status[2] = 'red'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1) 
        elif status[0] == "green" and status[2] == "red":
            status[0] = 'red'
            status[2] = 'green'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1)
        elif status[0] == "red" and status[2] == "red":
            status[0] = 'green'
            status[2] = 'green'
            status = dance(status, dice[0])
            print(status)
            return churras2(status, dice[1:], x+1)  

# churras(status, dice) consumes a list of strings, status, representing the 
#   intial block colours, and a list of the number between 2 and 12 inclusive,
#   called dice. The numbers in dice are the sums of two dice values after
#   being rolled, and the list dice has a length of 5. The function does not
#   produce anything, but instead prints the list of block colous at the end
#   of each of the rounds, until every block is either red or every block is
#   green. Once this happens, the function prints a completion message. 
# churras: (listof Str) (listof Nat) -> None
# Effects: In purpose statement
# Requires: Status is length 4, Dice is length 5
# Examples:
# churras(['red', 'green', 'green', 'green'],[11,4,12,3,10]) => None, and prints
# ['red', 'green', 'green', 'green']
# ['green', 'green', 'green', 'green']
# Let's eat. We are all very very hungry!

# churras(['red','red','green','green'], [7,8,8,11,6]) => None, and prints
# ['red', 'red', 'green', 'green']
# [‘red’, 'green', 'green', 'green']
# ['green', 'green', 'green', 'green']
# Let's eat. We are all very very hungry!

def churras (status, dice):
    return churras2(status,dice,0)         
   
# Test 1: every element in status is green
check.set_screen("prints status once, and then a completion message")
check.expect("Q4T1", churras(['green', 'green', 'green', 'green'], [2,3,4,5,6]), None)

# Test 2: every element in status in red
check.set_screen("prints status once, and then a completion message")
check.expect("Q4T2", churras(['red', 'red', 'red', 'red'], [2,3,4,5,6]), None)

# Test 3: Takes 1 step to get all one color
check.set_screen("prints status twice, and then prints the completion message")
check.expect("Q4T3", churras(['red', 'green', 'green', 'green'],[11,4,12,3,10]), None)

# Test 4: Takes 2 steps to get all one color
check.set_screen("prints status three times, and then prints the completion message")
check.expect("Q4T4", churras(['red','red','green','green'], [7,8,8,11,6]), None)

# Test 5: Takes 3 steps to get all one color
check.set_screen("prints status four times, and then prints the completion message")
check.expect("Q4T5", churras(['green','red','red','red'], [6,3,3,7,10]), None)

# Test 6: Takes 4 steps to get all one color
check.set_screen("prints status five times, and then prints the completion message")
check.expect("Q4T6", churras(['green','red','red','green'], [6,12,3,7,10]), None)

# Test 7: Takes all steps to get all one color
check.set_screen("prints status six times, and then prints the completion message")
check.expect("Q4T7", churras(['green','red','red','red'], [11,3,5,7,10]), None)
        
              
    

