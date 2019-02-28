# CS 232 - 04 - eal376
# Elizabeth Lujan
# April 18, 2018

import random
import collections

NUM_SIDES = 6     # Number of sides on each die
NUM_DICE = 5      # Number of dice in the game
NUM_ROLLS = 3     # Number of rolls for each test
NUM_TESTS = 1000  # Number of tests to perform

# ***** Definition of Die object class and methods go here ***

# PART I - DEFINING THE DIE CLASS
class Die():
    def __init__(self, number_of_sides = 0):
        self.sides = number_of_sides
        self.hidden_value = 0
    def roll(self):
        if (self.sides > 0):
            self.hidden_value = random.randint(1, self.sides)
    def value (self):
        return self.hidden_value


# ***** End of Die class definition **************************

# list of Die objects -> boolean
# expects a list of Die objects
# returns True if all values of the Die objects match (a "Yahtzee")
#     returns False otherwise

def is_yahtzee(the_dice):
    result = True
    for i in range(1, NUM_DICE):
        if the_dice[i].value() != the_dice[i-1].value():
            result = False
    return result

# list of Die objects -> nothing
# expects a list of Die objects
# returns nothing
# side effect: prints to screen the values on the dice

def print_dice(the_dice):
    print("The dice values are: {0}".format([i.value() for i in the_dice]))

# list of Die objects -> int
# expects a list of Die objects
#    examines the values of the dice, and determines which value
#    is most common
# returns that most common value found
# Examples: the_dice values of [1, 5, 4, 5, 5] will return 5
#           the_dice values of [2, 6, 2, 6, 4] will return 2 or 6

def best_value_to_keep(the_dice):
    # Create a counter dictionary of the values in the_dice[]
    dice_counter = collections.Counter(i.value() for i in the_dice)
    
    # Look for the greatest number of dice that match each other
    how_many_dice_match = max(dice_counter.values())
    
    # Find which value on the dice (that is, which key in the counter)
    # corresponds to how_many_dice_match (if a tie, either value is OK)
    for i in list(dice_counter.keys()):
        if dice_counter[i] == how_many_dice_match:
            value_to_keep = i
            
    # value_to_keep is now the most commonly found value on the dice
    return value_to_keep

# *************** play_yahtzee code goes here ********************

# list of Die objects -> boolean
# expects a list of Die objects
#     Rolls the dice NUM_ROLLS times to try to get a "Yahtzee"
#     A Yahtzee is when all the dice have the same value
#     returns True if a Yahtzee occurs, or False otherwise
#
# side effect: prints to the screen the values of the dice
#     (by calling print_dice(the_dice)) after each roll,
#     and a single-line "Yahtzee" or "No Yahtzee" message at the end

# PART II - Writing the play_yahtzee function goes here



def play_yahtzee(the_dice):

    for i in the_dice:
        i.roll()
        
    for i in range (0 , NUM_ROLLS):
        result = is_yahtzee(the_dice)
        print_dice(the_dice)
        if(result):
            print ("YAHZTEE")
            return result  
        val = best_value_to_keep(the_dice)
        for i in the_dice:
            if (i.value() != val):
                i.roll()

    print ("No Yaztee")
    return result
        



# *************** end play_yahtzee code **************************

# *** The "main" code to run play_yahtzee() NUM_TIMES times goes here ***

# PART III - Code to run play_yahtzee multiple times goes here
my_dice = []
for i in range (0,NUM_DICE):
    c= Die(NUM_SIDES)
    c.roll()
    my_dice.append(c)

wins = 0
for i in range (0, NUM_TESTS):
    result = play_yahtzee(my_dice)
    if result:
        wins = wins + 1
        
win_percent = (wins / NUM_TESTS) * 100
print ("Out of {}, we got {} yahtzees! ".format (NUM_TESTS, wins))
print ("Success rate is : {0:5.2f}%".format(win_percent))


# Now, write a loop to call play_yahtzee(my_dice) NUM_TIMES times.
# Use a local variable to keep track of the
# number of Yahtzees that occur, and compute the percentage of
# tests the resulted in a Yahtzee.  Print the number of tests,
# the number of Yahtzees, and the percentage of success
# to the screen in an easy to read and understand manner



# *** End of "main" code ***
