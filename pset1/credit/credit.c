#include <stdio.h>
#include <cs50.h>

int get_starting_num(long card_number, int power);

int main(void)
{
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0 || card_number > 9999999999999999);
    // Length of the card, used to get starting num
    int count = 0;
    // Non product digits
    int odd_count = 0;
    // Product digits
    int even_count = 0;
    // Copy of card number to be iterated over
    long num = card_number;
    // Calculates the sum of the product and non-product digits
    while (num > 0)
    {
        count ++;
        int digit = num % 10;
        num = num / 10;

        if (count % 2 == 0)
        {
            even_count = even_count + ((2 * digit) % 10);
            even_count = even_count + ((2 * digit) / 10);
        }
        else
        {
            odd_count += digit;
        }
    }

    // The value of the lugn algo
    int luhn_val = (odd_count + even_count) % 10;

    int starting_digits = get_starting_num(card_number, (count - 2));

    if (luhn_val == 0)
    {
        if ((starting_digits == 34 || starting_digits == 37) && count == 15)
        {
            printf("AMEX\n");
        }
        else if ((starting_digits == 51 || starting_digits == 52 || starting_digits == 53 || starting_digits == 54
                    || starting_digits == 55) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            if (((starting_digits / 10) == 4) && (count == 13 || count == 16))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Gets the starting 2 digits of the card number
int get_starting_num(long card_number, int power)
{
    for (int i = 0; i < power; i++)
    {
        card_number = card_number / 10;
    }
    return card_number;
}