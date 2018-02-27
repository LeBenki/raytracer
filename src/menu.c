/*
** menu.c for menu in /home/swaz/Epitech/Graphical/raytracer2/src/
**
** Made by Melvin Nalepka
** Login   <nalepk_m@epitech.eu>
**
** Started on  Wed May 24 22:57:36 2017 Melvin Nalepka
** Last update Sun May 28 16:27:05 2017 Melvin Nalepka
*/

#include "line.h"

int			catch_event(sfEvent *event, sfRenderWindow *window)
{
  if (event->type == sfEvtClosed)
    sfRenderWindow_close(window);
  if (event->type == sfEvtMouseButtonPressed &&
      event->mouseButton.x >= 716 && event->mouseButton.x <= 1119
      && event->mouseButton.y >= 387 && event->mouseButton.y <= 467)
    {
      sfRenderWindow_close(window);
      return (1);
      }
  if (event->type == sfEvtMouseButtonPressed &&
      event->mouseButton.x >= 716 && event->mouseButton.x <= 1119 &&
      event->mouseButton.y >= 563 && event->mouseButton.y <= 643)
    return (2);
  if (event->type == sfEvtMouseButtonPressed &&
      event->mouseButton.x >= 716 && event->mouseButton.x <= 1119
      && event->mouseButton.y >= 735 && event->mouseButton.y <= 815)
    sfRenderWindow_close(window);
  return (0);
}

int		process_menu_loop(sfRenderWindow *window, sfSprite *sprite,
				  sfTexture *texture, t_my_framebuffer *fb)
{
  sfEvent	event;
  int		opt;
  static int	help = 0;

  while (sfRenderWindow_isOpen(window))
    {
      event.type = 0;
      while (sfRenderWindow_pollEvent(window, &event))
	{
	  opt = catch_event(&event, window);
	  if (opt == 1)
	    return (1);
	  if (opt == 2)
	    {
	      switch_to_help(window, sprite, fb, texture);
	      help = 1;
	    }
	}
      if (sfKeyboard_isKeyPressed(sfKeyEscape) && help != 1)
	sfRenderWindow_close(window);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
  return (0);
}

void			fill_mode(sfVideoMode *mode)
{
  mode->width = 1920;
  mode->height = 1080;
  mode->bitsPerPixel = 32;
}

int			set_back(t_my_framebuffer *fb, int opt, sfTexture *texture)
{
  t_bmp			*background;

  background = NULL;
  if (opt == 0)
    if ((background = read_bmp("Raytracer_2.bmp")) == NULL)
      return (84);
  if (opt == 1)
    if ((background = read_bmp("melvin.bmp")) == NULL)
      return (84);
  display_bmp(background, fb, 0, 0);
  sfTexture_updateFromPixels(texture, fb->pixels, fb->width, fb->height, 0, 0);
  return (0);
}

int			start_menu(int ac, char **av)
{
  sfVideoMode		mode;
  sfRenderWindow	*window;
  sfTexture		*texture;
  sfSprite		*sprite;
  t_my_framebuffer	*fb;

  fill_mode(&mode);
  window = sfRenderWindow_create(mode, "Raytracer 2", sfClose, NULL);
  if (!window)
    return (84);
  texture = sfTexture_create(mode.width, mode.height);
  if (!texture)
    return (84);
  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);
  fb = my_framebuffer_create(mode.width, mode.height);
  if (set_back(fb, 0, texture) == 84)
    return (84);
  if (process_menu_loop(window, sprite, texture, fb) == 1)
    raytracer(ac, av);
  my_framebuffer_kill(fb);
  sfSprite_destroy(sprite);
  sfTexture_destroy(texture);
  sfRenderWindow_destroy(window);
  return (0);
}
