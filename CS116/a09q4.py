##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 9, Problem 4
## ***************************************************
##

import check

def make_list(input_file):
    f = open(input_file)
    dic = []
    country = f.readline()
    x=1
    while x != 0:
        data = country.split(",")
        if country == "":
            x = 0
        else:
            dic = dic + [[data[0], data[1], data[2]]]
            country = f.readline()
    return order(exp_imp_ratio(dic))

def exp_imp_ratio(lst):
    countries = []
    for i in lst:
        if i[1] == "":
            None
        else:
            countries = countries + [[i[0], (float(i[1])/float(i[2]))]]
    return countries

def order(lst):
    dic={}
    for i in lst:
        dic[i[1]] = i[0]
    return dic

def seperate():

    return keys


    
        
            
# country_summary(n, input_file) consumes a natural number n, and input file, 
#  a string representing the file name, and produces a list of strings
#  in alphabetically ascending order. The produced list should have all the n country
#  names having the lowest exp_imp_ratio. The function should also write the produced
#  list of strings to the file "trade_ratio.txt". If n is out of range, None
#  should be produced and the file "trade_ratio.txt" should be empty.
# country_summary(n, input_file): Nat Str -> (listof Str)
# Effects: Writes to file
# Examples:

def country_summary(n, input_file):
    f = open(input_file)
    t = open("trade_ratio.txt","w")
    dic = make_list(input_file)
    lst = ((seperate(list(dic.keys())))[0:n]).sort()
    list_ = ((seperate(list(dic.keys())))[0:n]).sort()
    try:
        while n != 0:
            t.write(list_[0] + "\n")
            list_ = list_[1:]
            n = n - 1
        f.close()
        return lst
    except:
        None

# Test 1:
check.set_file("trade_ratio.txt", "test.txt")
check.expect

    

#make_list("country_data.csv")
#country_summary(3, "country_data.csv")