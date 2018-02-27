/*
** filters.c for filters in /home/simon/MUL/raytracer2/src/
**
** Made by Simon Bineau
** Login   <simon.bineau@epitech.eu>
**
** Started on  Thu May 25 09:41:38 2017 Simon Bineau
** Last update Thu May 25 16:47:38 2017 Simon Bineau
*/

#include "line.h"

sfColor		my_get_color(t_my_framebuffer *framebuffer, int x, int y)
{
  sfColor	color;

  color.r = 0;
  color.g = 0;
  color.b = 0;
  if ((x <= 0 || y <= 0) ||
      (x >= framebuffer->width || y >= framebuffer->height))
    return (color);
  color.r = framebuffer->pixels[(framebuffer->width * y + x) * 4];
  color.g = framebuffer->pixels[(framebuffer->width * y + x) * 4 + 1];
  color.b = framebuffer->pixels[(framebuffer->width * y + x) * 4 + 2];
  return (color);
}

void			negative(t_my_framebuffer *fb,
				 int x, int y)
{
  sfColor		color;
  sfColor		new;

  color = my_get_color(fb, x, y);
  new.r = 255 - color.r;
  new.g = 255 - color.g;
  new.b = 255 - color.b;
  my_put_pixel(fb, x, y, new);
}

void			sepia(t_my_framebuffer *fb,
				 int x, int y)
{
  sfColor		color;
  sfColor		new;

  color = my_get_color(fb, x, y);
  new.r = (color.a * 0.393) + (color.g * 0.769) + (color.b * 0.189);
  new.g = (color.a * 0.349) + (color.g * 0.686) + (color.b * 0.168);
  new.b = (color.a * 0.272) + (color.g * 0.534) + (color.b * 0.131);
  my_put_pixel(fb, x, y, new);
}

void			black_white(t_my_framebuffer *fb,
				    int x, int y)
{
  sfColor		color;
  int			new;

  color = my_get_color(fb, x, y);
  new = (color.r + color.g + color.b) / 3;
  color.r = new;
  color.g = new;
  color.b = new;
  my_put_pixel(fb, x, y, color);
}

void		filters(t_my_framebuffer *fb, int mode)
{
  int		y;
  int		x;

  y = -1;
  while (++y < fb->height)
    {
      x = -1;
      while (++x < fb->width)
	{
	  if (mode == 1)
	    black_white(fb, x, y);
	  else if (mode == 2)
	    negative(fb, x, y);
	  else if (mode == 3)
	    sepia(fb, x, y);
	}
    }
}
