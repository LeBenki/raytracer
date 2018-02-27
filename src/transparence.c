/*
** transparence.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Tue Apr 25 10:12:37 2017 Lucas Benkemoun
** Last update Sun May 28 19:48:38 2017 Melvin Nalepka
*/

#include "line.h"

static sfVector3f	calcul_vector(sfVector3f normal,
				      sfVector3f vector, float n)
{
  sfVector3f		N;
  sfVector3f		V;
  sfVector3f		T;

  N = my_normalise(normal);
  V = my_normalise(vector);
  T.x = n * V.x + (n * V.x * N.x - (sqrt(1 + pow(n,
						 2) * pow((V.x * N.x), 2) - 1))) * N.x;
  T.y = n * V.y + (n * V.y * N.y - (sqrt(1 + pow(n,
						 2) * pow((V.y * N.y), 2) - 1))) * N.y;
  T.z = n * V.z + (n * V.z * N.z - (sqrt(1 + pow(n,
						 2) * pow((V.z * N.z), 2) - 1))) * N.z;
  return (T);
}

float		test_trans(t_ray *ray, sfVector3f point, sfVector3f T, int i)
{
  float		k;

  k = -1;
  if (ray->form[i] == 's')
    k = intersect_sphere(point, T, ray->radius[i]);
  if (ray->form[i] == 'p')
    k = intersect_plane(point, T);
  if (ray->form[i] == 'c')
    k = intersect_cone(point, T, ray->radius[i]);
  if (ray->form[i] == 'y')
    k = intersect_cylinder(point, T, ray->radius[i]);
  if (ray->form[i] == 'a')
    k = intersect_paraboloide(point, T, ray->radius[i]);
  if (ray->form[i] == 'h')
    k = intersect_hyperboloide(point, T, ray->radius[i]);
  return (k);
}

static void	init_vectors(t_ray *ray,
			     sfVector3f *point, sfVector3f *T, int j)
{
  point->x -= ray->pos[j].x;
  point->y -= ray->pos[j].y;
  point->z -= ray->pos[j].z;
  *point = rotate_xyz(*point, set_vectorff(ray->rot[j].x,
					 ray->rot[j].y,
					 ray->rot[j].z));
  *T = rotate_xyz(*T, set_vectorff(ray->rot[j].x,
				 ray->rot[j].y,
				 ray->rot[j].z));
}

float		my_find_k(sfVector3f point, sfVector3f T, int *i, t_ray *ray)
{
  sfVector3f	save;
  float		k;
  float		ret;
  int		j;
  sfVector3f	save2;

  j = 0;
  *i = 0;
  save = point;
  save2 = T;
  k = -1;
  ret = 123456789;
  while (j < ray->n)
    {
      if (j == ray->count && (j += 1))
	continue;
      point = save;
      T = save2;
      init_vectors(ray, &point, &T, j);
      k = test_trans(ray, point, T, j);
      if (k > 0 && k < ret)
	1 ? ret = k, *i = j : 0;
      j += 1;
    }
  return (ret > 0 ? ret : -1);
}

sfColor		get_transparence(t_ray *ray, sfVector3f normal,
				 sfVector3f point)
{
  sfVector3f	T;
  float		k;
  float		cosa;
  sfVector3f	norm;
  int		i;

  get_reflection(ray, normal, point);
  T = calcul_vector(normal, ray->dir_vector, ray->trans[ray->count]);
  k = my_find_k(point, T, &i, ray);
  if (k < 0)
    return (ray->color_trans[ray->count] = sfBlack);
  point.x = T.x * k + point.x;
  point.y = T.y * k + point.y;
  point.z = T.z * k + point.z;
  if (point.z > ray->limit[i].x)
    return ((ray->color_trans[ray->count] = sfBlack));
  if (point.z < ray->limit[i].y)
    return ((ray->color_trans[ray->count] = sfBlack));
  norm = test_norm(ray, point, i);
  T = calcul_light(ray->light, point);
  cosa = get_light_coef(T, norm);
  ray->color_trans[ray->count].r = ray->color[i].r * cosa;
  ray->color_trans[ray->count].g = ray->color[i].g * cosa;
  ray->color_trans[ray->count].b = ray->color[i].b * cosa;
  return (ray->color_trans[ray->count]);
}
