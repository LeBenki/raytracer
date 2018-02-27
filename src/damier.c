/*
** damier.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sun May 28 11:23:45 2017 Lucas Benkemoun
** Last update Sun May 28 11:23:49 2017 Lucas Benkemoun
*/

#include "line.h"

int	simp(int nbr)
{
  nbr = abs(nbr);
  nbr = round(nbr);
  return (nbr);
}

sfVector3f		damier(t_ray *ray, sfVector3f point, sfVector3f normal)
{
  static sfColor	color;
  static int		b = 1;

  if (ray->radius[ray->count] == 2)
    {
      if (b)
	color = ray->color[ray->count];
      b = 0;
      if (point.y > 0)
	point.x -= 15;
      if (simp(point.x) % (30) > 15 && simp(point.y) % (30) > 15)
        ray->color[ray->count] = color;
      else if (simp(point.x) % (30) < 15 && simp(point.y) % (30) < 15)
        ray->color[ray->count] = color;
      else
	ray->color[ray->count] =
	  set_color(color.r / 5, color.g / 5, color.b / 5, 255);
    }
  else if (ray->radius[ray->count] == 1)
    normal.y = 0 + cos(point.y / 10) * 10;
  return (normal);
}
