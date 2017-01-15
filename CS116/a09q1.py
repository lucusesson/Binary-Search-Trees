##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 9, Problem 1
## ***************************************************
##

import check

# towns(log) consumes a list of strings called log, and produces a dictionary with
#  the participants as keys and a list of the towns that participant has visited
#  as the value.
# towns: (listof Str) -> (dictof Str (listof Str))

def towns(log):
    dic2 = {}
    for x in log:
        x = x.split(",")
        name = x[0]
        town = x[1]
        if name in dic2:
            dic2[name] = dic2[name] + [town]
        
        else:
            dic2[name] = [town]
    return dic2

# remove(lst) consumes a list of strings called lst, and removes any repitition.
# remove(lst): (listof Str) -> (listof Str)

def remove(lst):
    t = []
    for x in lst:
        if x in t:
            t = t
        else:
            t = t + [x]
    return t



# tally(log) consumes a list of strings called log, which represents where
#   each participant visited, and produces a dictionary with the participants
#   as keys and the total points earned as the values. 
# tally: (listof Str) -> (dictof Str Nat)
# Requires: As per assignment
# Examples:
# tally([ "jsmith,Elora,2", "jsmith,St. Jacobs,4", "klee,Elora,3",
#         "proth,Conestogo,4", "kafka,Heidelberg,2", "klee,Heidelberg,5",
#         "kafka,Elora,1", "klee,St. Jacobs,5", "jsmith,Heidelberg,1"])
#      => { "jsmith" : 7, "klee" : 13, "kafka" : 3, "proth" : 4 }

# tally([ "ricky,Linwood,4", "janed,Linwood,3", "janed,Wallenstein,2",
#         "ricky,Linwood,5", "mog,Conestogo,2"])
#      => { "mog" : 2, "ricky" : None, "janed" : 5 }


def tally(log):
    dic1 = {}
    dic2 = towns(log)
    for x in log:
        x = x.split(",")
        name = x[0]
        town = x[1]
        points = int(x[2])
        if dic2[name] != remove(dic2[name]):
            dic1[name] = None
        elif name in dic1:
            dic1[name] = dic1[name] + points
        else:
            dic1[name] = points
    return dic1

        
# Test 1: 
check.expect("Q1T1", tally([ "jsmith,Elora,2", "jsmith,St. Jacobs,4", "klee,Elora,3", "proth,Conestogo,4", "kafka,Heidelberg,2", "klee,Heidelberg,5", "kafka,Elora,1", "klee,St. Jacobs,5", "jsmith,Heidelberg,1"]), { "jsmith" : 7, "klee" : 13, "kafka" : 3, "proth" : 4 })

# Test 2:
check.expect("Q1T2", tally([ "ricky,Linwood,4", "janed,Linwood,3", "janed,Wallenstein,2", "ricky,Linwood,5", "mog,Conestogo,2"]), { "mog" : 2, "ricky" : None, "janed" : 5 })

# Test 3:
check.expect("Q1T2", tally([]), {})
