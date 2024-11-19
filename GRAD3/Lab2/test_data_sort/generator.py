import random

def generate_random_name():
    first_names = ["Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank", "Ivy", "Jack"]
    last_names = ["Smith", "Johnson", "Brown", "Williams", "Jones", "Garcia", "Miller", "Davis", "Martinez", "Lopez"]
    return f"{random.choice(first_names)} {random.choice(last_names)}"


def generate_random_age():
    return random.randint(18, 90)


def generate_users_to_file(filename, count):
    with open(filename, "w") as file:
        for _ in range(count):
            name = generate_random_name()
            age = generate_random_age()
            file.write(f"{name} {age}\n")


if __name__ == "__main__":
    output_file = "/home/resk/main/c/C_MEPHI/GRAD3/Lab2/build/test_data_sort/user_input.txt"
    user_count = 10000  
    generate_users_to_file(output_file, user_count)
    print(f"Файл '{output_file}' сгенерирован с {user_count} пользователями.")