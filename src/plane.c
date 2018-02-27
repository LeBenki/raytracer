/*
** plane.c for raytracer2 in /home/benki/Epitech/raytracer2
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Mon May  1 17:08:13 2017 Lucas Benkemoun
** Last update Sun May 28 19:47:06 2017 Melvin Nalepka
*/

#include "line.h"

float		intersect_plane(sfVector3f eye_pos, sfVector3f dir_vector)
{
  float		k;

  if (dir_vector.z == 0)
    return (-1.0);
  return ((k = -eye_pos.z / dir_vector.z) < 0 ? -1.0 : k);
}

sfVector3f	get_normal_plane(int upward)
{
  sfVector3f	normal;

  normal.x = 0;
  normal.y = 0;
  if (upward)
    normal.z = 100;
  else
    normal.z = -100;
  return (normal);
}

float		draw_para(t_ray *ray, sfVector3f point)
{
  float		k1;
  float		k2;
  sfVector2f	v1;
  sfVector2f	v2;

  if (ray->limit[ray->count].x == 0 &&
      (pow(point.x, 2) + pow(point.y, 2)) >= pow(ray->limit[ray->count].y, 2))
    return (-1);
  v1.x = ray->limit[ray->count].y;
  v1.y = 0;
  v2.x = 0;
  v2.y = ray->limit[ray->count].z;
  k2 = v1.x * point.y - point.x * v1.y;
  k2 /= v2.y * v1.x - v1.y * v2.x;
  k1 = point.x - k2 * v2.x;
  k1 /= v1.x;
  if (ray->limit[ray->count].x == 1)
    return ((k1 > 0 && k2 > 0  && k1 <= 1 && k2 <= 1) ? 1 : -1);
  else if (ray->limit[ray->count].x == 2)
    return ((k1 > 0 && k2 > 0 && (k1 + k2 < 1)) ? 1 : -1);
  return (1);
}

float		draw_plane(t_ray *ray)
{
  float		cos_angle;
  sfVector3f	point;
  sfVector3f	l;
  sfVector3f	normal;

  point.x = ray->dir_vector.x * ray->k[ray->count] + ray->eye.x;
  point.y = ray->dir_vector.y * ray->k[ray->count] + ray->eye.y;
  point.z = ray->dir_vector.z * ray->k[ray->count] + ray->eye.z;
  if (draw_para(ray, point) < 0)
    return (ray->k[ray->count] = -1);
  normal = get_normal_plane(ray->pos[ray->count].z);
  normal = damier(ray, point, normal);
  normal = rotate_xyz(normal, set_vectorff(ray->rot[ray->count].x,
  					   ray->rot[ray->count].y,
  					   ray->rot[ray->count].z));
  l = calcul_light(ray->light, point);
  cos_angle = (normal.x * l.x + normal.y * l.y + normal.z * l.z);
  cos_angle /= (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)) *
		sqrt(pow(l.x, 2) + pow(l.y, 2) + pow(l.z, 2)));
  ray->color_trans[ray->count] = get_transparence(ray, normal, point);
  return (cos_angle);
}
