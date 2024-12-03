import sys
import random
import os

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

def generate_data(filename, num_records, min_age, max_age):
    try:
        with open(filename, 'w') as file:
            records = []
            for _ in range(num_records):
                first_name = random.choice(first_names)
                last_name = random.choice(last_names)
                age = random.randint(min_age, max_age)
                records.append(f"{age},{first_name} {last_name}")
            file.write("\n".join(records) + "\n")
    except Exception as e:
        print(f"An error occurred while writing to {filename}: {e}")

def main():
    num_records_large = 10000000
    num_records_small = 10000
    min_age = 1
    max_age = 99

    script_dir = os.path.dirname(os.path.abspath(__file__)) + "/test_data/"
    large_filename = os.path.join(script_dir, "data.txt")
    small_filename = os.path.join(script_dir, "small_data.txt")

    generate_data(large_filename, num_records_large, min_age, max_age)
    generate_data(small_filename, num_records_small, min_age, max_age)

if __name__ == "__main__":
    main()