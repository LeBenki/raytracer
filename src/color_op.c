/*
** color_op.c for color_op in /home/simon/MUL/raytracer2/src/
**
** Made by Simon Bineau
** Login   <simon.bineau@epitech.eu>
**
** Started on  Thu May 25 13:47:14 2017 Simon Bineau
** Last update Thu May 25 14:04:50 2017 Simon Bineau
*/

#include "line.h"

sfColor		color_add(sfColor a, sfColor b)
{
  sfColor	ret;

  ret.r = a.r + b.r;
  ret.g = a.g + b.g;
  ret.b = a.b + b.b;
  ret.a = a.a + b.a;
  return (ret);
}

sfColor		color_sub(sfColor a, sfColor b)
{
  sfColor	ret;

  ret.r = a.r - b.r;
  ret.g = a.g - b.g;
  ret.b = a.b - b.b;
  ret.a = a.a - b.a;
  return (ret);
}

sfColor		color_div(sfColor color, int d)
{
  sfColor	ret;

  ret.r = color.r / d;
  ret.g = color.g / d;
  ret.b = color.b / d;
  return (ret);
}
