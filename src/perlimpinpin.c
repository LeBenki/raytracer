/*
** perlimpinpin.c for perlimpinpin in /home/simon/MUL/raytracer2/src/
**
** Made by Simon Bineau
** Login   <simon.bineau@epitech.eu>
**
** Started on  Sat May 27 18:39:21 2017 Simon Bineau
** Last update Sun May 28 19:45:30 2017 Melvin Nalepka
*/

#include "line.h"

sfColor		interpolation(t_v va, t_v vb, float n)
{
  sfColor	ret;

  ret.r = va.color.r * (n - va.f)
      / (vb.f - va.f) + vb.color.r * (vb.f - n) / (vb.f - va.f);
  ret.g = va.color.g * (n - va.f)
      / (vb.f - va.f) + vb.color.g * (vb.f - n) / (vb.f - va.f);
  ret.b = va.color.b * (n - va.f)
      / (vb.f - va.f) + vb.color.b * (vb.f - n) / (vb.f - va.f);
  ret.a = 255;
  return (ret);
}

sfColor		color_table(float n, float f, sfColor def, sfVector3f point)
{
  t_v		v1;
  t_v		v2;
  t_v		v3;
  t_v		v4;

  def = sfWhite;
  n = cos(point.x - point.y - point.z - n);
  v1.f = f + 0;
  v1.color = set_color(0, 0, 255, 0);
  v2.f = f + 0.25;
  v2.color = set_color(75, 75, 255, 0);
  v3.f = f + 0.5;
  v3.color = set_color(150, 150, 255, 0);
  v4.f = f + 1;
  v4.color = set_color(225, 225, 255, 0);
  if (n >= v1.f && n < v2.f)
    return (interpolation(v1, v2, n));
  if (n >= v2.f && n < v3.f)
    return (interpolation(v2, v3, n));
  if (n >= v3.f && n < v4.f)
    return (interpolation(v3, v4, n));
  return (def);
}

float		noise(float x, float y, float z)
{
  float		n;

  n = (cos(x - y + z) - sin(x) + cos(z));
  n += 255;
  n /= 3 * cos(2);
  n *= cos(z + 0.2 - x);
  n = n - floor(n);
  if (n > 1 && n <= 2)
    return (-n -1);
  return (n);
}
