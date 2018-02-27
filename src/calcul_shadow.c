/*
** calcul_shadow.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Wed Mar 15 11:14:45 2017 Lucas Benkemoun
** Last update Sun May 28 12:25:45 2017 Lucas Benkemoun
*/

#include "line.h"

sfVector3f	calc_point(t_ray *ray, float k, sfVector3f eye)
{
  sfVector3f	point;

  point.x = ray->dir_vector.x * k + eye.x;
  point.y = ray->dir_vector.y * k + eye.y;
  point.z = ray->dir_vector.z * k + eye.z;
  return (point);
}

static void	test_shadow(t_ray *ray, sfVector3f l, char c, int i)
{
  if (ray->form[i] == 's' && c != 's')
    ray->shadow[i] = intersect_sphere(ray->shadow_p, l, ray->radius[i]);
  if (ray->form[i] == 'p' && c != 'p')
    ray->shadow[i] = intersect_plane(ray->shadow_p, l);
  if (ray->form[i] == 'c' && c != 'c')
    ray->shadow[i] = intersect_cone(ray->shadow_p, l, ray->radius[i]);
  if (ray->form[i] == 'y' && c != 'y')
    ray->shadow[i] = intersect_cylinder(ray->shadow_p, l, ray->radius[i]);
  if (ray->form[i] == 'a' && c != 'a')
    ray->shadow[i] = intersect_paraboloide(ray->shadow_p, l, ray->radius[i]);
  if (ray->form[i] == 'h' && c != 'h')
    ray->shadow[i] = intersect_hyperboloide(ray->shadow_p, l, ray->radius[i]);
  if (ray->form[i] ==  c)
    ray->shadow[i] = 2;
}

static sfVector3f	calcul_l(sfVector3f l, t_ray *ray, float k, int i)
{
  ray->shadow_p = calc_point(ray, k,
			     set_vectorff(ray->save.x - ray->pos[i].x,
					  ray->save.y - ray->pos[i].y,
					  ray->save.z - ray->pos[i].z));
  l = calcul_light(ray->light, ray->shadow_p);
  ray->shadow_p = rotate_zyx(ray->shadow_p,
			     set_vectorff(ray->rot[i].x,
					  ray->rot[i].y,
					  ray->rot[i].z));
  l = rotate_zyx(l,
		 set_vectorff(ray->rot[i].x,
			      ray->rot[i].y,
			      ray->rot[i].z));
  return (l);
}

float		calcul_shadow(t_ray *ray, float k, char c)
{
  int		i;
  sfVector3f	l;

  i = -1;
  while (++i < ray->n)
    {
      l = calcul_l(l, ray, k, i);
      if (ray->shadow_p.z > ray->limit[i].x ||
	  ray->shadow_p.z < ray->limit[i].y)
      	{
      	  ray->shadow[i] = 2;
      	  continue;
      	}
      test_shadow(ray, l, c, i);
    }
  i = -1;
  while (++i < ray->n)
    if (ray->shadow[i] < 1 && ray->shadow[i] > 0)
      return (-1);
  return (1);
}
