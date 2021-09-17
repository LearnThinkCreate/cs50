def main():
    while True:
        try:
            # Getting # and checking val
            height = int(input("Height: "))
            if height in range(1,9):
                break
        # Raising error if user is naughty
        except ValueError:
            print("You must enter a number")

    draw(height, height)

def draw(h, m):
    if (h == 0):
        return

    draw(h - 1, m)

    # drawing the first pyramid from left to right
    print(" " * (m-h) + "#" * h, end = "")
    # Adding middle space
    print("  ", end = "")
    # Drawing the right pyramid
    print("#" * h)

if __name__ == "__main__":
    main()