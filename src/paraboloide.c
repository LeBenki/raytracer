/*
** paraboloide.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Wed Feb 15 20:41:33 2017 Lucas Benkemoun
** Last update Sun May 28 19:39:43 2017 Melvin Nalepka
*/

#include "line.h"

static float	one_soluce(float a, float b)
{
  float		k1;

  k1 = -b / (2 * a);
  if (k1 > 0)
    return (k1);
  else
    return (-1.0);
}

static float	two_soluce(float a, float b, float delta)
{
  float		k1;
  float		k2;

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

float		intersect_paraboloide(sfVector3f eye,
				      sfVector3f dir, float p1)
{
  float		delta;
  float		a;
  float		b;
  float		c;

  a = pow(dir.x, 2) + pow(dir.y, 2);
  b = -p1 * dir.z + 2 * eye.x * dir.x + 2 * eye.y * dir.y;
  c = -p1 * eye.z + pow(eye.x, 2) + pow(eye.y, 2);
  delta = pow(b, 2) - (4 * a * c);
  if (delta > 0)
    return (two_soluce(a, b, delta));
  else if (delta < 0)
    return (-1.0);
  else
    return (one_soluce(a, b));
}

sfVector3f	get_normal_paraboloide(sfVector3f point, float rad)
{
  sfVector3f	normal;

  normal.x = point.x;
  normal.y = point.y;
  normal.z = -rad;
  return (normal);
}

float		draw_paraboloide(t_ray *ray)
{
  float		cos_angle;
  sfVector3f	point;
  sfVector3f	normal;
  sfVector3f	save;

  point.x = ray->dir_vector.x * ray->k[ray->count] + ray->eye.x;
  point.y = ray->dir_vector.y * ray->k[ray->count] + ray->eye.y;
  point.z = ray->dir_vector.z * ray->k[ray->count] + ray->eye.z;
  save = point;
  if (point.z > ray->limit[ray->count].x)
    return ((ray->k[ray->count] = -1));
  if (point.z < ray->limit[ray->count].y)
    return ((ray->k[ray->count] = -1));
  normal.x = ray->dir_vector.x * ray->k[ray->count] + ray->eye.x;
  normal.y = ray->dir_vector.y * ray->k[ray->count] + ray->eye.y;
  normal.z = -ray->radius[ray->count];
  normal = rotate_xyz(normal, set_vectorff(ray->rot[ray->count].x,
					   ray->rot[ray->count].y,
					   ray->rot[ray->count].z));
  point = calcul_light(ray->light, point);
  cos_angle = (normal.x * point.x + normal.y * point.y + normal.z * point.z);
  cos_angle /= (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)) *
		sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2)));
  ray->color_trans[ray->count] = get_transparence(ray, normal, save);
  return (cos_angle);
}
