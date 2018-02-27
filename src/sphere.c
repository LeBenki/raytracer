/*
** sphere.c for raytracer2 in /home/benki/Epitech/raytracer2
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Mon May  1 17:07:47 2017 Lucas Benkemoun
** Last update Sun May 28 19:47:28 2017 Melvin Nalepka
*/

#include "line.h"

float	deter_delta(float a, float b, float delta)
{
  float	k2;
  float	k1;

  if (delta > 0)
    {
      k1 = (-b - sqrt(delta)) / (2 * a);
      k2 = (-b + sqrt(delta)) / (2 * a);
      if (k1 < 0 && k2 < 0)
	return (-1.0);
      else if (k1 < 0)
	return (k2);
      else if (k2 < 0)
	return (k1);
      else
	return (k1 > k2 ? k2 : k1);
    }
  else if (delta < 0)
    return (-1.0);
  else
    {
      k1 = -b / (2 * a);
      return ((k1 > 0) ? k1 : -1.0);
    }
}

float		intersect_sphere(sfVector3f e,
				 sfVector3f dir_vector, float radius)
{
  float		delta;
  float		a;
  float		b;
  float		c;

  a = pow(dir_vector.x, 2) + pow(dir_vector.y, 2) + pow(dir_vector.z, 2);
  b = 2 * ((e.x * dir_vector.x + e.y * dir_vector.y + e.z * dir_vector.z));
  c = pow(e.x, 2) + pow(e.y, 2) + pow(e.z, 2) - pow(radius, 2);
  delta = pow(b, 2) - (4 * a * c);
  return (deter_delta(a, b, delta));
}

sfVector3f	get_normal_sphere(sfVector3f dir)
{
  sfVector3f	normal;

  normal.x = dir.x;
  normal.y = dir.y;
  normal.z = dir.z;
  return (normal);
}

float		draw_sphere(t_ray *ray)
{
  float		cos_angle;
  sfVector3f	point;
  sfVector3f	normal;

  point.x = ray->dir_vector.x * ray->k[ray->count] + ray->eye.x;
  point.y = ray->dir_vector.y * ray->k[ray->count] + ray->eye.y;
  point.z = ray->dir_vector.z * ray->k[ray->count] + ray->eye.z;
  if (ray->noise[ray->count] >= -1 && ray->noise[ray->count] <= 1)
    ray->color[ray->count] = color_table(noise(point.x,
					       point.y, point.z),
					 ray->noise[ray->count],
					 ray->color[ray->count], point);
  if (ray->texture[ray->count])
    ray->color[ray->count] = my_texture(point, ray->texture[ray->count]);
  if (point.z > ray->limit[ray->count].x)
    return ((ray->k[ray->count] = -1));
  if (point.z < ray->limit[ray->count].y)
    return ((ray->k[ray->count] = -1));
  normal = get_normal_sphere(point);
  point = calcul_light(ray->light, point);
  cos_angle = (normal.x * point.x + normal.y * point.y + normal.z * point.z);
  cos_angle /= (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)) *
		sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2)));
  ray->color_trans[ray->count] = get_transparence(ray, normal, point);
  return (cos_angle);
}
