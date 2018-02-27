/*
** anti_aliasing.c for anti_aliasing in /home/simon/MUL/raytracer2/src/
**
** Made by Simon Bineau
** Login   <simon.bineau@epitech.eu>
**
** Started on  Thu Apr 27 21:18:04 2017 Simon Bineau
** Last update Thu May 25 14:58:45 2017 Simon Bineau
*/

#include "line.h"

int	color_avg_8(t_my_framebuffer *fb, int i)
{
  int	n;
  int	test;
  int	color;

  n = 1;
  color = fb->pixels[i];
  test = 4;
  (fb->pixels[i - test] && (i % (fb->width - 1)) != 0)
    ? (color += fb->pixels[i - test], n++) : (0);
  (fb->pixels[i + test] && (i % fb->width) != 0)
    ? (color += fb->pixels[i + test], n++) : (0);
  (fb->pixels[i - fb->width * test] && (i % (fb->width - 1)) != 0)
    ? (color += fb->pixels[i - fb->width * test], n++) : (0);
  (fb->pixels[i + fb->width * test] && (i % fb->width) != 0)
    ? (color += fb->pixels[i + fb->width * test], n++) : (0);
  (fb->pixels[i - test + fb->width * test] && (i % (fb->width - 1)) != 0)
    ? (color += fb->pixels[i - test + fb->width * test], n++) : (0);
  (fb->pixels[i - test - fb->width * test] && (i % (fb->width - 1)) != 0)
    ? (color += fb->pixels[i - test - fb->width * test], n++) : (0);
  (fb->pixels[i + test + fb->width * test] && (i % fb->width) != 0)
    ? (color += fb->pixels[i + test + fb->width * test], n++) : (0);
  (fb->pixels[i + test - fb->width * test] && (i % fb->width) != 0)
    ? (color += fb->pixels[i + test - fb->width * test], n++) : (0);
  color /= n;
  return (color);
}

int	color_avg_4(t_my_framebuffer *fb, int i)
{
  int	n;
  int	test;
  int	color;

  n = 1;
  color = fb->pixels[i];
  test = 4;
  (fb->pixels[i - test] && (i % (fb->width)) != 1)
    ? (color += fb->pixels[i - test], n++) : (0);
  (fb->pixels[i + test] && (i % (fb->width)) != 0)
    ? (color += fb->pixels[i + test], n++) : (0);
  (fb->pixels[i - fb->width * test])
    ? (color += fb->pixels[i - fb->width * test], n++) : (0);
  (fb->pixels[i + fb->width * test])
    ? (color += fb->pixels[i + fb->width * test], n++) : (0);
  color /= n;
  return (color);
}

t_my_framebuffer	*anti_aliasing(t_my_framebuffer *current, int mode)
{
  int			i;
  t_my_framebuffer	*new;

  i = -1;
  if (!mode && mode != 4 && mode != 8)
    return (current);
  new = my_framebuffer_create(current->width, current->height);
  while (++i < current->width * current->height * 4)
    {
      if (mode == 4)
	new->pixels[i] = color_avg_4(current, i);
      else if (mode == 8)
	new->pixels[i] = color_avg_8(current, i);
    }
  return (new);
}
