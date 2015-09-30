#include "ft_philo.h"
 
void check_constant_errors(void)
{
    if (MAX_LIFE < 1 || EAT_T < 1 || THINK_T < 1 || TIMEOUT < 1)
    {
        ft_puterrdl("The constants variables must be greater than 0");
        exit(-1);
    }
}

int main()
{
    check_constant_errors();
    
    return 0; 
}