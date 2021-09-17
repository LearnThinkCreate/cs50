import re

def main():
    """
    Applying Luhn's Algo
    Multiplying every other digit (from the right) by 2
    and finding the sum. Then adding the sum of the digits
    not multiplied by 2
    Returns Credit Card Brand if valid Card and
    INVALID otherwise
    """

    cardNum = input("Number: ")

    if len(cardNum) % 2 == 0:
        products = list(range(0 , len(cardNum), 2))
        sums = list(range(1, len(cardNum), 2))
    else:
        products = list(range(1, len(cardNum), 2))
        sums = list(range(0, len(cardNum), 2))

    # Storing the products in a list
    ls = []
    for i in products:
        # Getting the product
        num = int(cardNum[i]) * 2
        # Converting to a string
        s = str(num)
        # Appending the digits to ls
        for c in s:
            ls.append(int(c))

    # Intializing the luhn_val with the sum of the products
    luhn_val = sum(ls)

    for i in sums:
        num = int(cardNum[i])
        luhn_val += num

    if luhn_val % 10 != 0 or len(cardNum) not in [13, 15, 16]:
        print("INVALID")
        return

    if re.search("^51|^52|^53|^54|^55", cardNum):
        print("MASTERCARD")
    elif re.search("^34|^37", cardNum):
        print("AMEX")
    elif re.search("^4", cardNum):
        print("VISA")
    else:
        print("INVALID")



if __name__ == "__main__":
    main()