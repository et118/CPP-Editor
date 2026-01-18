import random

with open("jokes.txt", "r") as file:
    print(random.choice(file.readlines()).strip())
