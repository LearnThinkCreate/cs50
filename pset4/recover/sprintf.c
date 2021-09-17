#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char buffer[20];

    int i = get_int("Please enter a int ");
    if (i < 10)
    {
       sprintf(buffer, "This is CS00%i.jpg", i);
       printf("%s\n", buffer);
    }
    else
    {
       sprintf(buffer, "This is CS0%i.jpg", i);
       printf("%s\n", buffer);
    }
}