import sys
import csv

def main():

    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py db.csv str.txt")

    people = []
    with open(sys.argv[1], "r") as file:
        # Reading in each row as dict
        reader = csv.DictReader(file)
        # appdending the dict to a list
        for row in reader:
            people.append(row)

    with open(sys.argv[2], "r") as file:
        text = file.readline()

    ## Creating dictionary to store counts of STR
    dna = {}
    for field in reader.fieldnames:
        if field == "name":
            pass
        else:
            dna[field] = 0

    # Finding the max str for each permutation in the text
    for key in dna:
        dna[key] = str_count(text, key)

    # Seeing if anyone matches the DNA profile picked up
    for person in people:
        match = False

        # Comparing the values of each persons STR
        for field in reader.fieldnames:
            if field == "name":
                pass
            else:
                # Converting person fields to INT
                person[field] = int(person[field])
                if person[field] == dna[field]:
                    match = True
                # Breaking immediatly if there is no match
                else:
                    match = False
                    break

        # Printing person name if there's a match and exiting programs
        if match:
            print(person["name"])
            exit(0)

    print("No match")



# Finds the max consecutive STR in a row
def str_count(seq, STR):
    # Intializing variables
    count = 0
    max_len = 0

    # Iterating over seq looking for the STR pattern
    for i in range(0, len(seq)):
        # If pattern found, adding to count
        if  seq[i: (i + len(STR))] == STR:
            k = 0
            while seq[(i + k):(i + k + len(STR))] == STR:
                count += 1
                k += len(STR)
        # Otherwise checking for new max_len and re-intializing count
        else:
            if count > max_len:
                max_len = count
            count = 0

    return max_len

if __name__ == "__main__":
    main()




