from cs50 import get_string
import string

def main():

    text = get_string("Text: ")

    letters = 0

    """
    Populating Coefecients
    coef[0] is the letter average
    coef[1] is the sentence average
    """
    coef = get_cli_coef(text)

    index = round(0.0588 * coef[0] - 0.296 * coef[1] - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade ", index)

def get_cli_coef(text):
    # Intializing variables
    words = 1
    letters = 0
    sentences = 0

    for c in text:
        if str.isalpha(c):
            letters += 1
        elif str.isspace(c):
            words += 1
        elif c in [".", "?", "!"]:
            sentences += 1

    L = (100 / words) * letters
    W = (100 / words) * sentences

    return [L, W]

if __name__ == "__main__":
    main()