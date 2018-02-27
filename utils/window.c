/*
** window.c for wireframe in /home/lucas99.06/Epitech/Semester1/Graph_Prog/wireframe/src
**
** Made by Lucas Benkemoun
** Login   <benke_l@epitech.net>
**
** Started on  Fri Dec  9 14:45:45 2016 Lucas Benkemoun
** Last update Sun May 28 19:56:31 2017 Melvin Nalepka
*/

#include "line.h"

sfRenderWindow*		create_window(char* name, int width, int height)
{
  sfRenderWindow*	window;
  sfVideoMode		mode;

  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, name, sfResize | sfClose, NULL);
  if (window == NULL)
    return (NULL);
  return (window);
}

int			my_end(t_my_framebuffer *fb, sfTexture *texture,
			       sfSprite *s, sfRenderWindow *window)
{
  my_framebuffer_kill(fb);
  sfSprite_destroy(s);
  sfTexture_destroy(texture);
  sfRenderWindow_destroy(window);
  return (0);
}

t_my_framebuffer	*my_framebuffer_create(int width,
					       int height)
{
  int			i;
  t_my_framebuffer	*fb;

  i = 0;
  fb = malloc(sizeof(t_my_framebuffer));
  fb->width = width;
  fb->height = height;
  fb->pixels = malloc(width * height * 4 * sizeof(*(fb->pixels)));
  if ((fb->pixels) == NULL)
    return (NULL);
  while (i < width * height * 4)
    {
      fb->pixels[i] = 0;
      i++;
    }
  return (fb);
}

void			my_framebuffer_kill(t_my_framebuffer *fb)
{
  free(fb->pixels);
  free(fb);
}
