/*
** init.c for raytracer2 in /home/coudoul/Epitech/raytracer2/bonus
**
** Made by Baptiste Coudoulet
** Login   <baptiste.coudoulet@epitech.eu>
**
** Started on  Sun May 28 13:22:24 2017 Baptiste Coudoulet
** Last update Sun May 28 14:28:02 2017 root
*/

#include "line.h"

void		running_display(t_my_framebuffer *fb, t_pixel pixel)
{
  if (pixel.i % 50 == 0)
    {
      sfRenderWindow_drawSprite(fb->window, fb->s, NULL);
      sfRenderWindow_display(fb->window);
      sfTexture_updateFromPixels(fb->texture, fb->pixels, fb->width,
				 fb->height, 0, 0);
    }
  my_put_pixel(fb, pixel.j, pixel.i, pixel_to_color(pixel));
}

t_mpi		init_mpi_struct(char *processor_name, int world_size,
				int world_rank)
{
  t_mpi		mpi;

  mpi.processor_name = processor_name;
  mpi.world_size = world_size;
  mpi.world_rank = world_rank;
  return (mpi);
}
