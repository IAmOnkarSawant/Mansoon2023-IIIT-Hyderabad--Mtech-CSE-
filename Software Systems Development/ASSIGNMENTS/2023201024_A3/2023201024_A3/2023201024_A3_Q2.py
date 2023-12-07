import csv
from rich.console import Console
from rich.table import Table
from tabulate import tabulate

csv_header = ["First Name", "Last Name", "Age", "Nationality", "Role", "Runs", "Balls", "Wickets", "Strike Rate"]

directory = []

console = Console()

def load_data():
    try:
        with open("cricketer_directory.csv", "r", newline="") as file:
            reader = csv.DictReader(file)
            directory.extend(reader)
    except FileNotFoundError:
        pass

def save_data():
    with open("cricketer_directory1.csv", "w", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=csv_header)
        writer.writeheader()
        writer.writerows(directory)

def show_directory():
    if not directory:
        console.print("No entries found.")
        return

    table_data = [csv_header]
    for entry in directory:
        table_data.append([entry[field] for field in csv_header])

    table = tabulate(table_data, headers="firstrow", tablefmt="grid")
    console.print(table)

def add_entry():
    entry = {}
    for field in csv_header:
        if field in ["Batsmen", "Bowler", "All-rounder", "Wk-Batsmen"]:
            entry[field] = 0
        else:
            entry[field] = input(f"Enter {field}: ")

    if not entry["Strike Rate"]:
        if entry["Role"] == "Batsman":
            runs = int(entry["Runs"])
            balls = int(entry["Balls"])
            entry["Strike Rate"] = runs / balls if balls > 0 else 0
        elif entry["Role"] == "Bowler":
            wickets = int(entry["Wickets"])
            balls = int(entry["Balls"])
            entry["Strike Rate"] = wickets / balls if balls > 0 else 0
        elif entry["Role"] == "All-rounder":
            runs = int(entry["Runs"])
            balls = int(entry["Balls"])
            bat_sr = runs / balls if balls > 0 else 0
            wickets = int(entry["Wickets"])
            entry["Strike Rate"] = max(bat_sr, (wickets / balls)) if balls > 0 else 0

    directory.append(entry)
    console.print("Entry added successfully.")

def remove_entry():
    show_directory()
    if not directory:
        return
    try:
        index = int(input("Enter the index of the entry to remove: "))
        if 0 <= index < len(directory):
            removed_entry = directory.pop(index)
            console.print("Removed Entry:")
            console.print(removed_entry)
        else:
            console.print("Invalid index. Entry not removed.")
    except ValueError:
        console.print("Invalid input. Index must be an integer.")

def update_entry():
    show_directory()
    if not directory:
        return
    try:
        index = int(input("Enter the index of the entry to update: "))
        if 0 <= index < len(directory):
            entry = directory[index]
            for field in csv_header:
                value = input(f"Enter new {field} (leave blank to keep current value): ")
                if value:
                    entry[field] = value
            if entry["Role"] == "Batsman":
                runs = int(entry["Runs"])
                balls = int(entry["Balls"])
                entry["Strike Rate"] = runs / balls if balls > 0 else 0
            elif entry["Role"] == "Bowler":
                wickets = int(entry["Wickets"])
                balls = int(entry["Balls"])
                entry["Strike Rate"] = wickets / balls if balls > 0 else 0
            elif entry["Role"] == "All-rounder":
                runs = int(entry["Runs"])
                balls = int(entry["Balls"])
                bat_sr = runs / balls if balls > 0 else 0
                wickets = int(entry["Wickets"])
                entry["Strike Rate"] = max(bat_sr, (wickets / balls)) if balls > 0 else 0
            console.print("Entry updated successfully.")
        else:
            console.print("Invalid index. Entry not updated.")
    except ValueError:
        console.print("Invalid input. Index must be an integer.")

def search_entries():
    field = input("Enter attribute to search (e.g., 'Role', 'Nationality', 'Age'): ")
    value = input(f"Enter value for {field}: ")
    matching_entries = [entry for entry in directory if entry[field] == value]
    if matching_entries:
        console.print("\nMatching Entries:")
        table_data = [csv_header]
        for entry in matching_entries:
            table_data.append([entry[field] for field in csv_header])
        table = tabulate(table_data, headers="firstrow", tablefmt="grid")
        console.print(table)
    else:
        console.print("No matching entries found.")

if __name__ == "__main__":
    while True:
        console.print("\nMenu:")
        console.print("1. Load Entries")
        console.print("2. Display Directory")
        console.print("3. Add Entry")
        console.print("4. Remove Entry")
        console.print("5. Update Entry")
        console.print("6. Search Entries")
        console.print("7. Save and Exit")
        choice = input("Enter your choice: ")
        if choice == "1":
            load_data()
        if choice == "2":
            show_directory()
        elif choice == "3":
            add_entry()
        elif choice == "4":
            remove_entry()
        elif choice == "5":
            update_entry()
        elif choice == "6":
            search_entries()
        elif choice == "7":
            save_data()
            console.print("Cricketer's Directory saved to 'cricketer_directory.csv'. Exiting.")
            break
        else:
            console.print("Invalid choice. Please choose a valid option.")
