/*
** my_getnbr.c for my_getnbr in /home/lucas99.06/CPool_Day04
** 
** Made by Lucas Benkemoun
** Login   <lucas99.06@epitech.net>
** 
** Started on  Sat Oct  8 17:26:08 2016 Lucas Benkemoun
** Last update Sat Mar 18 10:29:41 2017 Lucas Benkemoun
*/

float	my_getfloat(char *str)
{
  int	i;
  float	resultat;
  int	neg;
  float	count;
  float	n;

  count = 1;
  i = -1;
  neg = 1;
  resultat = 0;
  while (str[++i] == '-')
    neg *= -1;
  --i;
  while (str[++i] >= '0' && str[i] <= '9')
    resultat = (resultat * 10) + str[i] - 48;
  (str[i] == '.') ? ++i : 0;
  while ((str[i] >= 48) && (str[i] <= 57))
    {
      n = str[i] - 48;
      count /= 10;
      resultat += count * n;
      i += 1;
    }
  return (resultat * neg);
}

int	my_getnbr(char *str)
{
  int	i;
  int	resultat;
  int	neg;

  i = 0;
  neg = 1;
  resultat = 0;
  while (str[i] == '-')
    {
      neg *= -1;
      i += 1;
    }
  while ((str[i] >= 48) && (str[i] <= 57))
    {
      resultat = (resultat * 10) + str[i] - 48;
      i += 1;
    }
  return (resultat * neg);
}
