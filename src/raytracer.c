/*
** main.c for bootstrap in /home/benki/Epitech/bsraytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Tue Feb  7 17:15:42 2017 Lucas Benkemoun
** Last update Sun May 28 17:02:46 2017 Lucas Benkemoun
*/

#include "line.h"

void		my_compare(t_my_framebuffer *framebuffer,
			   t_ray *ray)
{
  float		save;
  int		col;
  int		bool_dark;

  ray->count = -1;
  save = 60000000;
  col = -1;
  bool_dark = 1;
  while (++ray->count < ray->n)
    if (ray->k[ray->count] < save && ray->k[ray->count] > 0)
	{
	  save = ray->k[ray->count];
	  col = ray->count;
  	  bool_dark = 0;
	}
  if (bool_dark && !ray->background)
    my_put_pixel(framebuffer, ray->j, ray->i, sfBlack);
  else if (bool_dark)
    my_put_pixel(framebuffer, ray->j, ray->i,
		 get_pixel_bmp(ray->background,
			       (ray->j * ray->background->w) / ray->width,
			       (ray->i * ray->background->h) / ray->height));
  else
    my_put_pixel(framebuffer, ray->j, ray->i, cal_col(ray->color[col],
  						      ray->cos_angle[col], ray, col));
}

void		raytrace_scene(t_my_framebuffer *fb, t_ray *ray)
{
  while (ray->i <= ray->height)
    {
      ray->j = 0;
      while (ray->j <= ray->width)
	{
	  my_reset(ray);
	  ray->count = -1;
	  while (++ray->count < ray->n)
	    {
	      my_reset(ray);
	      ray->dir_vector = calc_dir_vector(ray->dist_toplan,
						set_vector(ray->width, ray->height),
						set_vector(ray->j, ray->i));
	      my_eye_rotate(ray);
	      calcul(ray);
	    }
	  my_compare(fb, ray);
	  ray->j++;
	}
      ray->i++;
    }
}

int			raytracer(int ac, char **av)
{
  sfRenderWindow        *window;
  sfTexture             *texture;
  sfSprite              *s;
  t_my_framebuffer      *fb;
  t_ray                 *ray;

  if (ac != 2 && write(2, "Usage :  ./raytracer [file.xml]\n", 32))
    return (84);
  if ((!(ray = malloc(sizeof(*ray)))) || (!(ray = read_xml(ray, av[1]))))
    return (84);
  if (!(window = create_window("Raytracer 2", ray->width, ray->height)))
    return (84);
  if (!(texture = sfTexture_create(ray->width, ray->height)))
    return (84);
  1 ? s = sfSprite_create(), sfSprite_setTexture(s, texture, sfTrue) : 0;
  fb = my_framebuffer_create(ray->width, ray->height);
  1 ? fb->texture = texture, fb->window = window, fb->s = s : 0;
  thread_raytrace_scene(fb, ray);
  fb = anti_aliasing(fb, ray->AA);
  filters(fb, ray->filtre);
  if (ray->expor == 1)
    frame_to_bmp(fb);
  sfTexture_updateFromPixels(texture, fb->pixels, fb->width, fb->height, 0, 0);
  process_game_loop(window, s);
  return (my_end(fb, texture, s, window));
}

int		process_game_loop(sfRenderWindow *window, sfSprite *sprite)
{
  sfEvent	event;

  while (sfRenderWindow_isOpen(window))
    {
      while (sfRenderWindow_pollEvent(window, &event))
	if (event.type == sfEvtClosed)
	  sfRenderWindow_close(window);
      if (sfKeyboard_isKeyPressed(sfKeyEscape))
	  sfRenderWindow_close(window);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
  return (0);
}
