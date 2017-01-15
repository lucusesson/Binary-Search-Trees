##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 7, Problem 3
## ***************************************************
##

import check

# find_word(lst) consumes a list of strings, lst, and produces the first element
#    in lst, and returns the empty list if lst is empty.
# find_word: (listof Str) -> (Anyof Str [])
def find_word(lst):
    if lst == []:
        return lst
    else:
        return lst[0]


# make_list(text, word, lst) consumes a string text, a string, word, and a list,
#    lst. It produces a list similar to text, where each word in text is
#    its own element in the returned list.
# make_list: Str Str (listof Str) -> (listof Str)
# Requires: word start as "", and lst start as []
def make_list(text, word, lst):
    if text == "":
        return lst +[word]
    elif text[0] != " " and text[0] != "," and text[0] != ".":
        return make_list(text[1:], word+text[0], lst)
    else:
        x = word 
        return make_list(text[1:], "", lst + [x])
    
# count_times(lst, word) consumes a list of strings, lst, and a string, word,
#    and produces the number of times word is found in lst.
# count_times: (listof Str) Str -> Str
def count_times(lst, word):
    return str(len(list(filter(lambda x: x == word, lst))))

# how_many(text) consumes a list of strings, text, and produces None. Instead
#    it prints the number of each words there are in text, each on a seperate
#    line.
# word_count: (listof Str) -> None
# Effects: Prints the number of each words there are in text, each on a seperate
#    line.
def how_many(lst):

    if find_word(lst) == []:
        pass
    else:
        word = find_word(lst)
        print(word + " - " + count_times(lst, word) + " times.")
        new_lst = list(filter(lambda x: x != word, lst))
        return how_many(new_lst)

# word_count(text) consumes a list of strings, text, and produces None. Instead
#    it prints the number of total words there are in text, and then each on a
#    seperate line prints the number of times each word appears in text.
# word_count: (listof Str) -> None
# Effects: Prints the number of each words there are in text, each on a seperate
#    line.
# Examples:
# word_count(“”) prints: There are a total of 0 words.

# word_count(“Up,up,up,to the sky,    ... 3 ups.”) prints:
# There are a total of 8 words.
# 3 - 1 times.
# Up - 1 times.
# sky - 1 times. 
# the - 1 times. 
# to - 1 times. 
# up - 2 times.
# ups - 1 times.

def word_count(text):
    if text == "":
            print("There are a total of 0 words.")
    else:    
        lst = list(filter(lambda x: x != "", make_list(text,"",[])))
        lst.sort()

        words = str(len(lst))

        print("There are a total of" + " " + words + " " + "words.")
        return how_many(lst)

# Test 1: text is empty
check.set_screen("prints: There are a total of 0 words")
check.expect("Q3T1", word_count(""), None)

# Test 2: text uses "." and "," as seperators
check.set_screen("prints total word count in text, as well as the number of occurrences of each word")
check.expect("Q3T2", word_count("Up,up,up,to the sky,    ... 3 ups."), None)

# Test 3: text is a long paragraph
check.set_screen("prints total word count in text, as well as the number of occurrences of each word")
check.expect("Q3T3", word_count("Once upon a time, there was a mountain. In the mountain, there was a temple. In the temple, there was an old monk. The old monk was telling a story to a young monk. The story went like this, once upon a time, there was a mountain..."), None)

# Test 4: text contains symbols, and many oddly placed seperators
check.set_screen("prints total word count in text, as well as the number of occurrences of each word")
check.expect("Q3T4", word_count("mixed-with-symbols!!! ..............hi2342648 @#$%^&* hy djhflsklfjksljfksl 87383748383939      ........"), None)





        


    
        
        
    