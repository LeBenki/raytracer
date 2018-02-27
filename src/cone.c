/*
** intersect_cyl.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Wed Feb  8 20:48:51 2017 Lucas Benkemoun
** Last update Sun May 28 19:34:06 2017 Melvin Nalepka
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

float		intersect_cone(sfVector3f eye,
			       sfVector3f dir, float radius)
{
  float		delta;
  float		a;
  float		b;
  float		c;

  if (radius <= 0 || radius >= 90)
    return (-1.0);
  a = -pow(tan(radius / (180 / M_PI)), 2) * pow(dir.z, 2);
  a += pow(dir.x, 2) + pow(dir.y, 2);
  b = -2 * pow(tan(radius / (180 / M_PI)), 2) * eye.z * dir.z;
  b += 2 * eye.x * dir.x + 2 * eye.y * dir.y;
  c = -pow(tan(radius / (180 / M_PI)), 2) * pow(eye.z, 2);
  c += pow(eye.y, 2) + pow(eye.x, 2);
  delta = pow(b, 2) - (4 * a * c);
  if (delta > 0)
    return (two_soluce(a, b, delta));
  else if (delta < 0)
    return (-1.0);
  else
    return (one_soluce(a, b));
}

sfVector3f	get_normal_cone(sfVector3f dir, float angle)
{
  sfVector3f	normal;
  float		r;

  normal.x = dir.x;
  normal.y = dir.y;
  r = tan(-angle * M_PI / 180);
  normal.z = r * dir.z;
  return (normal);
}

float		draw_cone(t_ray *ray)
{
  float		cos_angle;
  sfVector3f	dir;
  sfVector3f	normal;
  sfVector3f	point;

  dir.x = ray->dir_vector.x * ray->k[ray->count] + ray->eye.x;
  dir.y = ray->dir_vector.y * ray->k[ray->count] + ray->eye.y;
  dir.z = ray->dir_vector.z * ray->k[ray->count] + ray->eye.z;
  point = dir;
  if (dir.z > ray->limit[ray->count].x)
    return ((ray->k[ray->count] = -1));
  if (dir.z < ray->limit[ray->count].y)
    return ((ray->k[ray->count] = -1));
  normal = get_normal_cone(dir, ray->radius[ray->count]);
  normal = rotate_xyz(normal, set_vectorff(ray->rot[ray->count].x,
  					   ray->rot[ray->count].y,
  					   ray->rot[ray->count].z));
  dir = calcul_light(ray->light, dir);
  cos_angle = (normal.x * dir.x + normal.y * dir.y + normal.z * dir.z);
  cos_angle /= (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)) *
		sqrt(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2)));
  ray->color_trans[ray->count] = get_transparence(ray, normal, point);
  return (cos_angle);
}
