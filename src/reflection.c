/*
** transparence.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Tue Apr 25 10:12:37 2017 Lucas Benkemoun
** Last update Sun May 28 12:29:41 2017 Lucas Benkemoun
*/

#include "line.h"

sfVector3f	test_norm(t_ray *ray, sfVector3f point, int i)
{
  sfVector3f	vec;

  if (ray->form[i] == 's')
    vec = get_normal_sphere(point);
  if (ray->form[i] == 'p')
    vec = get_normal_plane(-25);
  if (ray->form[i] == 'c')
    vec = get_normal_cone(point, ray->radius[i]);
  if (ray->form[i] == 'y')
    vec = get_normal_cylinder(point);
  if (ray->form[i] == 'a')
    vec = get_normal_paraboloide(point, ray->radius[i]);
  if (ray->form[i] == 'h')
    vec = get_normal_hyperboloide(point, ray->radius[i]);
  return (vec);
}

static sfVector3f	calcul_vector(sfVector3f normal, sfVector3f vector)
{
  sfVector3f		norm;
  sfVector3f		dir;
  sfVector3f		R;

  norm = my_normalise(normal);
  dir = my_normalise(vector);
  R.x = -2 * norm.x * dir.x * norm.x + dir.x;
  R.y = -2 * norm.y * dir.y * norm.y + dir.y;
  R.z = -2 * norm.z * dir.z * norm.z + dir.z;
  return (R);
}

sfColor		get_reflection(t_ray *ray, sfVector3f normal,
				 sfVector3f point)
{
  sfVector3f	T;
  float		k;
  float		cosa;
  sfVector3f	norm;
  int		i;

  i = 0;
  T = calcul_vector(normal, ray->dir_vector);
  k = my_find_k(point, T, &i, ray);
  if (k < 0)
    return (ray->color_refl[ray->count] = sfBlack);
  point.x = T.x * k + point.x;
  point.y = T.y * k + point.y;
  point.z = T.z * k + point.z;
  if (point.z > ray->limit[i].x)
    return ((ray->color_refl[ray->count] = sfBlack));
  if (point.z < ray->limit[i].y)
    return ((ray->color_refl[ray->count] = sfBlack));
  norm = test_norm(ray, point, i);
  T = calcul_light(ray->light, point);
  cosa = get_light_coef(T, norm);
  ray->color_refl[ray->count].r = ray->color[i].r * cosa;
  ray->color_refl[ray->count].g = ray->color[i].g * cosa;
  ray->color_refl[ray->count].b = ray->color[i].b * cosa;
  return (ray->color_refl[ray->count]);
}
