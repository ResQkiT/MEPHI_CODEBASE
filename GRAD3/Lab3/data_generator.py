import random
import sys

# List of sample first names
first_names = [
    "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace",
    "Hank", "Ivy", "Jack", "Kate", "Luke", "Mia", "Nate", "Olivia",
    "Paul", "Quinn", "Ryan", "Sophia", "Tom", "Ursula", "Victor",
    "Wendy", "Xander", "Yara", "Zach", "Aaron", "Bella", "Carter",
    "Derek", "Ella", "Felix", "Gina", "Henry", "Isla", "Jake",
    "Kylie", "Leo", "Maya", "Nina", "Oscar", "Piper", "Quincy",
    "Riley", "Sophie", "Troy", "Uma", "Vera", "Will", "Xena",
    "Yasmine", "Zane"
]

# List of sample last names
last_names = [
    "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis",
    "Miller", "Wilson", "Moore", "Taylor", "Anderson", "Thomas",
    "Jackson", "White", "Harris", "Martin", "Thompson", "Garcia",
    "Martinez", "Robinson", "Clark", "Rodriguez", "Lewis", "Lee",
    "Walker", "Hall", "Allen", "Young", "Hernandez", "King",
    "Wright", "Lopez", "Hill", "Scott", "Green", "Adams", "Baker",
    "Gonzalez", "Nelson", "Carter", "Mitchell", "Perez", "Roberts",
    "Turner", "Phillips", "Campbell", "Parker", "Evans", "Edwards",
    "Collins", "Stewart", "Sanchez", "Morris", "Rogers", "Reed",
    "Cook", "Morgan", "Bell", "Murphy", "Bailey", "Rivera"
]

# Default values
num_records = 10000000
min_age = 1
max_age = 99
filename = "/home/resk/main/c/C_MEPHI/GRAD3/Lab3/test_data/data.txt"

# Check for command line arguments
if len(sys.argv) > 1:
    num_records = int(sys.argv[1])
if len(sys.argv) > 2:
    min_age = int(sys.argv[2])
if len(sys.argv) > 3:
    max_age = int(sys.argv[3])
if len(sys.argv) > 4:
    filename = sys.argv[4]

# Generate and write records to the file
try:
    with open(filename, 'w') as file:
        records = []
        for _ in range(num_records):
            # Select a random first name and last name
            first_name = random.choice(first_names)
            last_name = random.choice(last_names)
            # Generate a random age
            age = random.randint(min_age, max_age)
            # Append the record to the list
            records.append(f"{age},{first_name} {last_name}")
        
        # Write all records to the file at once
        file.write("\n".join(records) + "\n")

    print(f"{num_records} records have been written to {filename}.")
except Exception as e:
    print(f"An error occurred while writing to the file: {e}")
