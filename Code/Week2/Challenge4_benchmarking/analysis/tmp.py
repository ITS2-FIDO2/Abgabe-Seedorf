import os

directory = os.fsencode('./data')
for file in os.listdir(directory):
    fn = os.fsdecode(file)
    filename = "./data/" + fn
    print(filename)
