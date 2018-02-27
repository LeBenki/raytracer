/*
** my_strncpy.c for my_strncpy in /home/lucas99.06/CPool_Day06
** 
** Made by Lucas Benkemoun
** Login   <lucas99.06@epitech.net>
** 
** Started on  Mon Oct 10 09:40:38 2016 Lucas Benkemoun
** Last update Sun May 28 19:51:54 2017 Melvin Nalepka
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	i;

  i = 0;
  while (i < n)
    {
      dest[i] = src[i];
      i += 1;
    }
  dest[i] = 0;
  return (dest);
}
