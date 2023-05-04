#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string credit;
    int digittest;
    int mod;
    // only continue with digit input
    do
    {
        credit = get_string("Credit card no: ");
        //check for numbers only input
        digittest = 0;
        for (int i = 0; credit[i] != '\0'; i++)
        {
            if (isdigit(credit[i]) == 0)
            {
                digittest++;
            }
        }
    }
    // input ok if digittest > 0
    while (digittest > 0);
    // if length is smaller 13 digits or longer 16 digits it is not a credit card
    if (strlen(credit) < 13 || strlen(credit) > 16)
    {
        printf("INVALID\n");
        return (0);
    }
    int temp;
    int luhn1 = 0;
    // Luhn algorythm part 1 with multiplication and summing of every second digit from the right starting with the second
    for (int i = strlen(credit) - 1; i > 0; i -= 2)
    {
        //strlen counts w/o "\0", index is length -1 !
        // "-48" for conversion of char value (ascii) to dec value
        if (i >= 1)
        {
            temp = ((credit[i - 1] - 48) * 2);
            if (temp >= 10)
            {
                while (temp != 0)
                {
                    luhn1 += (temp % 10);
                    temp = temp / 10;
                }
            }
            else
            {
                luhn1 += temp;
            }
        }
    }
    // Luhn algorythm part 2 with adding of every second digit from the right starting with the first
    for (int i = strlen(credit) - 1; i >= 0; i -= 2)
    {
        luhn1 += ((credit[i]) - 48);
    }
    // part 3 of Luhn algorythm cheking with mod 10
    mod = luhn1 % 10;
    printf("mutiplication result digits as of Luhn: %i\n", luhn1);
    printf("Mod: %i\n", mod);
    //printing results depending of Luhn and credit card brand criterias
    if ((strlen(credit) == 13 || strlen(credit) == 16) && mod == 0 && credit[0] == '4')
    {
        printf("VISA\n");
    }
    else if (strlen(credit) == 15 && mod == 0 && (credit[0] == '3' && (credit[1] == '4' || credit[1] == '7')))
    {
        printf("AMEX\n");
    }
    else if (strlen(credit) == 16 && mod == 0 && (credit[0] == '5' && (credit[1] <= '5' && credit[1] >= '1')))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}