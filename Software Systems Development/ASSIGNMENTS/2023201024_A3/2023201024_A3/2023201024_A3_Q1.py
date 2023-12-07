from rich.console import Console
from rich.table import Table
import csv

directory = {}


def add_participants():
    inp = input('Names separeted by , : ')
    names = inp.split(',')
    for it in names:
        cleaned = it.strip(' ._')
        print(cleaned)
        directory[cleaned] = 0
        

def add_expense():
    paidBy = input('')
    amount = float(input(''))
    inp = input('')
    names = inp.split(',')
    
    if paidBy not in directory:
        print(f"Error: Participant '{paidBy}' not found.")
        return
    else:
        cleaned = paidBy.strip(' ._')
        directory[cleaned] = directory[cleaned] - amount

    length = len(names)
    parts = amount/length
    
    for name in names:
        cleaned = name.strip(' ._')
        if cleaned not in directory:
            print(f"Participant '{cleaned}' not found.")
            return
    
    for name in names:
        cleaned = name.strip(' ._')
        directory[cleaned] = directory[cleaned] + parts


def show_participants():
    print('-----------------')
    print('      Names      ')
    print('-----------------')
    for key, value in directory.items():
        print(f"{key} : {round(value, 3)}")

def show_expenses():
    console = Console()
    master = Table(title="")
    master.add_column("Expenses", justify="center")
    for key, val in directory.items():
        table = Table(title=str(key))
        columns = ["Amount", "Owes or Gets Back"]
        state = "Gets Back" if val < 0 else "Owes"
        rows = [str(abs(round(val, 3))), state]
        
        for column in columns:
            table.add_column(column, justify="center")
        
        table.add_row(*rows, style='bright_green')
        master.add_row(table)
    console.print(master)

def save_to_csv():
    with open('expenses.csv', 'w', newline='') as csvfile:
        fields = ['Participant', 'Balance']
        writer = csv.DictWriter(csvfile, fieldnames=fields)

        writer.writeheader()
        for participant, balance in directory.items():
            writer.writerow({'Participant': participant, 'Balance': round(balance, 3)})


if __name__ == "__main__":

    while True:
        print("\nMenu:")
        print("1. Add participant(s)")
        print("2. Add expense")
        print("3. Show all participants")
        print("4. Show expenses")
        print("5. Exit/Export")
        
        ch = input()
        
        if ch == "1":
            add_participants()
        elif ch == "2":
            add_expense()
        elif ch == "3":
            show_participants()
        elif ch == "4":
            show_expenses()
        elif ch == "5":
            save_to_csv() 
            break
        else:
            print("Invalid choice. Please choose a valid option.")
