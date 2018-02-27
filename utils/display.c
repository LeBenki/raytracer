/*
** display.c for display in /home/benki/mylib
** 
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
** 
** Started on  Sun Jan 29 11:42:32 2017 Lucas Benkemoun
** Last update Sun May 28 19:50:19 2017 Melvin Nalepka
*/

#include "line.h"

void	my_putchar(char c)
{
  if (write(1, &c, 1) == -1)
    return;
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      my_putchar(str[i]);
      i++;
    }
}

void	my_showtab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    {
      my_putstr(tab[i]);
      my_putchar('\n');
      i++;
    }
}

int	my_put_nbr(int nb)
{
  int	compteur;
  int	save;

  save = nb;
  compteur = 1;
  if (nb < 0)
    {
      my_putchar('-');
      nb *= -1;
      save *= -1;
    }
  while (nb / compteur >= 10)
    compteur *= 10;
  while (compteur > 0)
    {
      nb = save;
      nb /= compteur;
      nb %= 10;
      my_putchar(nb + 48);
      compteur /= 10;
    }
  return (0);
}

int	my_strlen(char *s)
{
  int	i;

  i = 0;
  while (s[i])
    i++;
  return (i);
}
