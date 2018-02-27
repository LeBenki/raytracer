/*
** my_rotate.c for raytracer1 in /home/benki/Bureau/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sat Mar 18 10:21:07 2017 Lucas Benkemoun
** Last update Mon May 22 13:24:13 2017 Lucas Benkemoun
*/

#include "line.h"

void	my_eye_rotate(t_ray *ray)
{
  ray->eye = rotate_xyz(ray->eye,
			set_vectorff(ray->eyerot.x,
				     ray->eyerot.y,
				     ray->eyerot.z));
  ray->dir_vector = rotate_xyz(ray->dir_vector,
			       set_vectorff(ray->eyerot.x,
					    ray->eyerot.y,
					    ray->eyerot.z));
}

void	my_form_rotate(t_ray *ray)
{
  ray->eye = rotate_zyx(ray->eye,
			set_vectorff(ray->rot[ray->count].x,
				     ray->rot[ray->count].y,
				     ray->rot[ray->count].z));
  ray->dir_vector = rotate_zyx(ray->dir_vector,
			       set_vectorff(ray->rot[ray->count].x,
					    ray->rot[ray->count].y,
					    ray->rot[ray->count].z));
}
