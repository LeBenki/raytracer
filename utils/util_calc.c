/*
** utils_calc.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Mon Mar  6 16:14:11 2017 Lucas Benkemoun
** Last update Sun May 28 19:54:08 2017 Melvin Nalepka
*/

#include "line.h"

char		*my_epur_str(char *str)
{
  char		*new;
  int		i;
  int		j;

  new = malloc(my_strlen(str) + 1);
  i = -1;
  j = 0;
  while (str[++i])
    {
      if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	new[j++] = str[i];
    }
  new[j] = 0;
  return (new);
}

void		my_reset(t_ray *ray)
{
  ray->eye.z = ray->save.z;
  ray->eye.y = ray->save.y;
  ray->eye.x = ray->save.x;
}

sfVector3f	calcul_light(sfVector3f light, sfVector3f point)
{
  sfVector3f	dir;

  dir.x = light.x - point.x;
  dir.y = light.y - point.y;
  dir.z = light.z - point.z;
  return (dir);
}
sfColor		transrefl_color(sfColor color, t_ray *ray, int count)
{
  float		t;
  float		r;

  t = ray->trans[count];
  r = ray->refl[count];
  if (ray->trans[count])
    {
      color.r = ray->color_trans[count].r * t + color.r * (1 - t);
      color.g = ray->color_trans[count].g * t + color.g * (1 - t);
      color.b = ray->color_trans[count].b * t + color.b * (1 - t);
    }
  if (ray->refl[count])
    {
      color.r = ray->color_refl[count].r * r + color.r * (1 - r);
      color.g = ray->color_refl[count].g * r + color.g * (1 - r);
      color.b = ray->color_refl[count].b * r + color.b * (1 - r);
    }
  return (color);
}

sfColor		cal_col(sfColor color, float f, t_ray *ray, int count)
{
  sfVector3f	col;

  col.x = (float)ray->colorlight.r / (float)255;
  col.y = (float)ray->colorlight.g / (float)255;
  col.z = (float)ray->colorlight.b / (float)255;
  if (f > 0)
    {
      color.r *= f;
      color.g *= f;
      color.b *= f;
      color.r *= ray->brillance * col.x * ray->lum;
      color.g *= ray->brillance * col.y * ray->lum;
      color.b *= ray->brillance * col.z * ray->lum;
      return (transrefl_color(color, ray, count));
    }
  else
    return (sfBlack);
}
