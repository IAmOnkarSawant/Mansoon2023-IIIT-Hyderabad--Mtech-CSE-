import csv
import matplotlib.pyplot as plt
import numpy as np

# Function to read expenses data from a CSV file
def read_expenses(filename):
    data = {}
    with open(filename, mode='r') as file:
        csv_reader = csv.DictReader(file)
        for row in csv_reader:
            data[row['Participant']] = float(row['Balance'])
    return data

# Function to create a pie chart for a given dataset
def create_pie(data, title):
    labels = [name for name, _ in data]
    sizes = [size for _, size in data]
    explode = [0.1 if size == max(sizes) else 0 for size in sizes]  

    plt.figure(figsize=(8, 8))
    plt.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%', startangle=140)
    plt.axis('equal')  

    legend_labels = [f"{name}: {size}" for name, size in data]
    plt.legend(legend_labels, loc="best")

    plt.title(title)
    plt.show()

# Function to calculate and plot batting and bowling strike rates
def calc_and_plot_sr():
    fields = ["First Name", "Last Name", "Age", "Nationality", "Role", "Runs", "Balls", "Wickets", "Strike Rate"]
    cricketers = []

    with open("cricketer_directory.csv", "r", newline="") as file:
        reader = csv.DictReader(file)
        cricketers.extend(reader)

    names = []
    bat_srs = []
    bowl_srs = []

    for player in cricketers:
        name = f"{player['First Name']} {player['Last Name']}"
        names.append(name)
        if player["Role"] == "Batsman":
            runs = int(player["Runs"])
            balls = int(player["Balls"])
            bat_sr = runs / balls if balls > 0 else 0
            bat_srs.append(bat_sr)
            bowl_srs.append(0)  
        elif player["Role"] == "Bowler":
            wickets = int(player["Wickets"])
            balls = int(player["Balls"])
            bowl_sr = wickets / balls if balls > 0 else 0
            bat_srs.append(0)  
            bowl_srs.append(bowl_sr)
        else:
            runs = int(player["Runs"])
            balls = int(player["Balls"])
            bat_sr = runs / balls if balls > 0 else 0
            wickets = int(player["Wickets"])
            bowl_sr = wickets / balls if balls > 0 else 0
            bat_srs.append(bat_sr)
            bowl_srs.append(bowl_sr)

    x = np.arange(len(names))

    width = 0.35

    plt.figure(figsize=(12, 6))
    plt.bar(x - width/2, bat_srs, width, label="Batting SR")
    plt.bar(x + width/2, bowl_srs, width, label="Bowling SR")

    plt.xticks(x, names, rotation=90)
    plt.xlabel("Players")
    plt.ylabel("Strike Rate")
    plt.title("Batting and Bowling Strike Rates")
    plt.legend()
    plt.tight_layout()
    plt.show()

while True:
    print("\nMenu:")
    print("1. Create Pie Charts for Expenses")
    print("2. Calculate and Plot Batting and Bowling Strike Rates")
    print("3. Exit")

    choice = input("Enter your choice (1/2/3): ")

    if choice == "1":
        expenses_data = read_expenses('expenses.csv')
        owes = [(name, balance) for name, balance in expenses_data.items() if balance < 0]
        gets_back = [(name, -balance) for name, balance in expenses_data.items() if balance > 0]
        create_pie(owes, "Owes")
        create_pie(gets_back, "Gets Back")
    elif choice == "2":
        calc_and_plot_sr()
    elif choice == "3":
        print("Exiting the program.")
        break
    else:
        print("Invalid choice. Please choose a valid option.")
