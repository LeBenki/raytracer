/*
** calcul.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Mon Mar  6 19:45:19 2017 Lucas Benkemoun
** Last update Sat May 27 10:56:59 2017 Lucas Benkemoun
*/

#include "line.h"

void		calcul(t_ray *ray)
{
  int		i;

  i = -1;
  ray->eye.x -= ray->pos[ray->count].x;
  ray->eye.y -= ray->pos[ray->count].y;
  ray->eye.z -= ray->pos[ray->count].z;
  my_form_rotate(ray);
  while (ray->calcul[++i].c)
    if (ray->calcul[i].c == ray->form[ray->count])
	ray->calcul[i].func(ray);
}
