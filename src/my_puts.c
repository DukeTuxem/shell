#include "shell.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  write(1, str, strlen(str));
}

int	my_puterror(char *str)
{
  write(2, str, strlen(str));
  return (1);
}

void	my_put_nbr(int nb)
{
  int	tmp;
  int	div;

  div = 1;
  if (nb < 0)
    {
      my_putchar('-');
      nb = -nb;
    }
  tmp = nb;
  while (tmp > 9)
    {
      tmp = tmp / 10;
      div = div * 10;
    }
  while (div > 0)
    {
      my_putchar(nb / div + '0');
      nb = nb % div;
      div = div / 10;
    }
}
