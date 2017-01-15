##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 8, Problem 4
## ***************************************************
##

import check

# found(word, x, letter) consumes three strings, word, x and letter.
#   The function then inserts letter into x, based on where it should be
#   in relation to word. 
# found: Str Str Str -> Str
# Requires: len(letter) = 1
def found(word, x, letter):
    n = x
    y = 0
    for i in word:
        if letter == i:
            n = n[0:y] + i + n[y+1:]
            y = y + 1
        else:
            y = y + 1
    return n
            

# hangman(word, guesses) consumes a lowercase, non-empty, non-whitespace, 
#   alphabetic string word, and a positive natural number guesses, and the game
#   behaves as the demos from the assignment.
# hangman: Str Nat -> None
# Effects: Prints according to demos as per assignment.
#          User input called on user to guess each letter. 
#          The user input is either a correct guess, incorrect guess, or a prompt
#          to quit. What happens for each input as per assignment demos. 
# Examples:
# hangman("amazing", 100) => None, but prints the following:
# Welcome to hangman.
# Your word is -------
# Please guess a letter or type quit: z

# Your word is ---z---
# Please guess a letter or type quit: quit
# Goodbye!


# hangman("yo",4) => None, but prints the following:
# Welcome to hangman.
# Your word is --
# Please guess a letter or type quit: y

# Your word is y-
# Please guess a letter or type quit: o
# Congratulations the word is yo.

def hangman(word, guesses):
    x = "-" * len(word)
    y = ""
    print("Welcome to hangman.")
    while guesses != 0 and x != word and y != "quit":
        print("Your word is " + x)
        user_input = input("Please guess a letter or type quit: ")
        if user_input == "quit":
            print("Goodbye!")
            y = "quit"
        elif user_input in x:
            print("You already guessed " + user_input + ". Guesses remaining: " + str(guesses))
            print("")
        elif found(word, x, user_input) != x:
            print("")
            x = found(word, x, user_input)
        elif guesses - 1 == 0:
            guesses = guesses - 1
        else:
            guesses = guesses - 1
            print("Sorry, try again. Guesses remaining: " + str(guesses))
            print("")            
    if guesses == 0:
        print("Game over. The correct word is " + word + ".")
    elif x == word:
        print("Congradulations the word is " + word + ".")
    else:
        None