/*
** line.c for bswireframe in /home/lucas99.06/Epitech/Semester1/Graph_Prog/bswireframe
**
** Made by Lucas Benkemoun
** Login   <benke_l@epitech.net>
**
** Started on  Mon Nov 14 10:14:07 2016 Lucas Benkemoun
** Last update Thu May 25 16:29:33 2017 Simon Bineau
*/

#include "line.h"

void	my_put_pixel(t_my_framebuffer *framebuffer,
		     int x, int y, sfColor color)
{
  if ((x <= 0 || y <= 0) ||
      (x >= framebuffer->width || y >= framebuffer->height))
    return;
  framebuffer->pixels[(framebuffer->width * y + x) * 4] = color.r % 256;
  framebuffer->pixels[(framebuffer->width * y + x) * 4 + 1] = color.g % 256;
  framebuffer->pixels[(framebuffer->width * y + x) * 4 + 2] = color.b % 256;
  framebuffer->pixels[(framebuffer->width * y + x) * 4 + 3] = 255;
}
