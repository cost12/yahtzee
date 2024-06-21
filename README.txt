This is a command line yahtzee game that I made some time when I was bored, probably during covid.

The game will prompt for 2 names then play. Enter AI as a name to play against AI (the AI is just random and terrible). 

Commands are:
roll - rolls the dice
hold x - hold die x so it is not rolled on the next roll
release x - release die x so it is rolled on the next roll
print dice - print the current state of the dice
print score - print the current player's score card
ones, twos, threes, fours, fives, sixes, 3k, 4k, fh, ss, ls, chance, yahtzee - end your turn and score the roll

There are still a couple errors, the end condition isn't checked appropriately which can cause some games to never end. You can also always assign a roll to yahtzee with no consequences.