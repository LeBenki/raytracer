/*
** menu2.c for menu in /home/swaz/Epitech/Graphical/raytracer2/src/
**
** Made by Melvin Nalepka
** Login   <nalepk_m@epitech.eu>
**
** Started on  Sat May 27 23:12:13 2017 Melvin Nalepka
** Last update Sat May 27 23:35:35 2017 Melvin Nalepka
*/

#include "line.h"

int		process_help_loop(sfRenderWindow *window, sfSprite *sprite)
{
  while (sfRenderWindow_isOpen(window))
    {
      if (sfKeyboard_isKeyPressed(sfKeyEscape))
	return (0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
  return (0);
}

int		switch_to_help(sfRenderWindow *window,
			       sfSprite *sprite,
			       t_my_framebuffer *fb, sfTexture *texture)
{
  set_back(fb, 1, texture);
  process_help_loop(window, sprite);
  set_back(fb, 0, texture);
  return (0);
}
