# SSD Assignment no 3 - Python

## Question no 1

### explaination
You have to design a Menu based Expense Tracker. The menu will be of the
following format:
Menu:
● Add participant(s)
● Add expense
● Show all participants
● Show expenses
● Exit/Export.

### running the code:
- ```bash python 2023201024_A3_Q1.py```
### Assumptions:
- multiple names will be given using comma as seperator
- the person who paid the bill will not automatically included into the participants list, if person who pays is involved then his expense has to be given in list
- while showing in the table I have used very close styling as it was given in question, but it not exactly same
- apropriate error messages added

## Question no 2
### explaination
You have been made the analyst for the IPL team “Gachibowli Gorillas”. You have to
build a “Cricketer’s Directory” in python. The directory consists of a list of entries.
Each entry can store details such as:
1. First Name
2. Last Name
3. Age
4. Nationality
5. Role (Batsmen, Bowler, All-rounder, Wk-Batsmen)
6. Runs
7. Balls
8. Wickets
9. Strike Rate
For Calculating Strike Rate:
If the player is a batsmen, then Batting Strike rate = Runs/Balls
If the player is a bowler, then Bowling Strike rate = Wickets/Balls
If the player is an All-rounder, then Strike rate = max(Batting Strike rate, Bowling
Strike rate)

### running the code:
- ```bash python 2023201024_A3_Q2.py```
### Assumptions:
- while updating and deleting I am choosing the record based on index value.
- calulated the strike rate only if it not provided by user
- apropriate error messages added


## Question no 3

### explaination
For this question it is mandatory that you use the library matplotlib and no other
data visualization library. This is an extension of the first 2 questions. The
expenses.csv you generated in the first question will be used as the base for
creating pie charts here
### running the code:
- ```bash python 2023201024_A3_Q3.py```
### Assumptions:
- assumed that the -ve value shows the data Gets back,  +ve owes
- I have assumed from the example given that For batsman only batting average would be shown, for Bowler only bowling average is shown. and for all rounder both will be shown
- while showing the bowling and batting strike rate I ave recalulated. so if user provides some wrong strike rate while, entry it will be corrected over here to increase the accuracy of visualization
- apropriate error messages added