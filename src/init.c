/*
** init.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Tue Mar  7 16:54:21 2017 Lucas Benkemoun
** Last update Sun May 28 19:45:03 2017 Melvin Nalepka
*/

#include "line.h"

void		init_limit(t_ray *ray)
{
  int		i;

  i = -1;
  while (++i < ray->n)
    {
      ray->noise[i] = ray->limit[i].x = 800000;
      ray->limit[i].y = -800000;
      ray->limit[i].z = 0;
      ray->trans[i] = 0;
      ray->refl[i] = 0;
      ray->texture[i] = NULL;
    }
}

sfColor		init_color(char *str)
{
  sfColor	vec;
  int		i;

  i = 0;
  while (str[i] && ((str[i] < '0' || str[i] > '9') && str[i] != '-'))
    i++;
  vec.r = my_getnbr(&str[i]);
  while (str[i] && str[i] != ',')
    i++;
  vec.g = my_getnbr(&str[i + 1]);
  i++;
  while (str[i] && str[i] != ',')
    i++;
  vec.b = my_getnbr(&str[i + 1]);
  return (vec);
}

sfVector2f	init_two(char *str)
{
  sfVector2f	vec;
  int		i;

  i = 0;
  while (str[i] && ((str[i] < '0' || str[i] > '9') && str[i] != '-'))
    i++;
  vec.x = my_getfloat(&str[i]);
  while (str[i] && str[i] != ',')
    i++;
  vec.y = my_getfloat(&str[i + 1]);
  return (vec);
}

sfVector3f	init_three(char *str)
{
  sfVector3f	vec;
  int		i;

  vec.z = i = 0;
  while (str[i] && ((str[i] < '0' || str[i] > '9') && str[i] != '-'))
    i++;
  vec.x = my_getfloat(&str[i]);
  while (str[i] && str[i] != ',')
    i++;
  vec.y = my_getfloat(&str[i + 1]);
  i++;
  while (str[i] && str[i] != ',')
    i++;
  if (str[i] && str[i + 1])
    vec.z = my_getfloat(&str[i + 1]);
  return (vec);
}

float		init_one(char *str)
{
  float		f;
  int		i;

  i = 0;
  while (str[i] && ((str[i] < '0' || str[i] > '9') && str[i] != '-'))
    i++;
  f = my_getfloat(&str[i]);
  return (f);
}
