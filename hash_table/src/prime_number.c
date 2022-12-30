#include <math.h>
#include "prime_number.h"

/*Check if number is prime*/
int 
is_prime(const int num) 
{
    if (num < 2) 
    {
        return -1; 
    }
    for (int i = 2; i < num; i++) 
    {
        if ((num % i) == 0) 
        {
            return 0;
        }
    }
    return 1;
}

/*find next prime number larger than num*/
int 
next_prime_number(int num) 
{
    while (is_prime(num) != 1) 
    {
        num++;
    }
    return num;
}